#include "ExistsUETestCharacter.h"
#include "ExistsUETestProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "TP_WeaponComponent.h"
#include "ExistsUETestWidgetComponent.h"
#include "ExistsUETestGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/PlayerInformationWidget.h"
#include "ExistsUETestDelegates.h"
#include "Subsytems/ScoreSubsystem.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AExistsUETestCharacter::AExistsUETestCharacter()
{	
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	bReplicates = true;

	SetCanBeDamaged(true);

	PlayerInformationWidgetComponent = CreateDefaultSubobject<UExistsUETestWidgetComponent>(TEXT("WidgetComponent"));
	PlayerInformationWidgetComponent->SetupAttachment(RootComponent);

	PlayerInformationWidgetComponent->SetDisplayOnOwner(false);
}

void AExistsUETestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UPlayerInformationWidget* PlayerInformationWidget = PlayerInformationWidgetComponent->GetCastedWidget<UPlayerInformationWidget>())
	{
		PlayerInformationWidget->SetCharacter(this);
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(RegularDamageHandler, this, &ThisClass::ApplyRegularDamage, RegularDamageInterval, true);

	OnDeath.AddUObject(this, &ThisClass::OnCharacterDeath);

	Health = MaxHealth;
}

void AExistsUETestCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnDeath.RemoveAll(this);
	
	GetWorld()->GetTimerManager().ClearTimer(RegularDamageHandler);

	if (UScoreSubsystem* ScoreSubsystem = GetWorld()->GetSubsystem<UScoreSubsystem>())
	{
		ScoreSubsystem->AddLogEntry(this);
	}
}

void AExistsUETestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExistsUETestCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExistsUETestCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AExistsUETestCharacter::ApplyRegularDamage()
{
	UGameplayStatics::ApplyDamage(this, RegularDamage, GetController(), nullptr, UDamageType::StaticClass());
}

void AExistsUETestCharacter::OnCharacterDeath()
{
	GetWorld()->GetTimerManager().ClearTimer(RegularDamageHandler);

	if (UScoreSubsystem* ScoreSubsystem = GetWorld()->GetSubsystem<UScoreSubsystem>())
	{
		ClientDemonstarateScores(ScoreSubsystem->GetTopEntries());
	}
}

void AExistsUETestCharacter::OnPlayerNameReplicated()
{
	OnPlayerNameChanged.Broadcast(PlayerName);
}

void AExistsUETestCharacter::OnHealthReplicated()
{
	OnHealthChanged.Broadcast(Health);
}

void AExistsUETestCharacter::ClientSetPlayerName_Implementation()
{
	UExistsUETestGameInstance* GameInstance = GetGameInstance<UExistsUETestGameInstance>();
	ServerSetPlayerName(GameInstance->GetPlayerName());
}

void AExistsUETestCharacter::ServerSetPlayerName_Implementation(const FString& NewPlayerName)
{
	PlayerName = NewPlayerName;
	OnPlayerNameChanged.Broadcast(PlayerName);
}

void AExistsUETestCharacter::ClientDemonstarateScores_Implementation(const TArray<FLogEntry>& Entries)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);

	FExistsUETestDelegates::OnDemonstrateTopScores.Broadcast(Entries);
}

void AExistsUETestCharacter::AddScore(float Score)
{
	CurrentScore += Score;
}

void AExistsUETestCharacter::SetHealth(float InHealth)
{
	if (!bIsDead)
	{
		InHealth = FMath::Clamp(InHealth, 0.0f, MaxHealth);

		if (InHealth != Health)
		{
			Health = InHealth;

			OnHealthChanged.Broadcast(Health);

			if (Health <= 0.0f)
			{
				bIsDead = true;
				OnDeath.Broadcast();
			}
		}
	}
}

void AExistsUETestCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AExistsUETestCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AExistsUETestCharacter::SetRifle(UTP_WeaponComponent* InWeapon)
{
	Weapon = InWeapon;
}

bool AExistsUETestCharacter::GetHasRifle()
{
	return Weapon != nullptr;
}

void AExistsUETestCharacter::Heal(float Amount)
{
	SetHealth(Health + Amount);
}

void AExistsUETestCharacter::PullPlayerName()
{
	ClientSetPlayerName();
}

float AExistsUETestCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (!bIsDead)
	{
		SetHealth(Health - DamageAmount);

		if (AExistsUETestCharacter* Character = Cast<AExistsUETestCharacter>(DamageCauser))
		{
			FExistsUETestDelegates::OnPlayerHit.Broadcast(this, Character);

			if (bIsDead)
			{
				FExistsUETestDelegates::OnPlayerKilled.Broadcast(this, Character);
			}
		}

		return DamageAmount;
	}
	
	return 0.0f;
}

void AExistsUETestCharacter::ServerFire_Implementation()
{
	if (Weapon)
	{
		Weapon->ServerFire();
	}
}

void AExistsUETestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AExistsUETestCharacter, PlayerName);
	DOREPLIFETIME(AExistsUETestCharacter, Health);
}
