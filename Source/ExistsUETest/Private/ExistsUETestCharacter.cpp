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
}

void AExistsUETestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(RegularDamageHandler, this, &ThisClass::ApplyRegularDamage, RegularDamageInterval, true);

	OnDeath.AddDynamic(this, &ThisClass::OnCharacterDeath);
}

void AExistsUETestCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnDeath.RemoveAll(this);
	GetWorld()->GetTimerManager().ClearTimer(RegularDamageHandler);
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
	SetHealth(Health - RegularDamage);
}

void AExistsUETestCharacter::OnCharacterDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Player has died"));
}

void AExistsUETestCharacter::SetHealth(float InHealth)
{
	Health = FMath::Clamp(InHealth, 0.0f, MaxHealth);

	if (Health <= 0.0f)
	{
		OnDeath.Broadcast();
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

float AExistsUETestCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	SetHealth(Health - DamageAmount);

	return DamageAmount;
}

void AExistsUETestCharacter::ServerFire_Implementation()
{
	if (Weapon)
	{
		Weapon->ServerFire();
	}
}
