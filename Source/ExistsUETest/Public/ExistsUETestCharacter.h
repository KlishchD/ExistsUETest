#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ExistsUETestCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UTP_WeaponComponent;
class UExistsUETestWidgetComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerNameChanged, const FString&);

UCLASS(config=Game)
class AExistsUETestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AExistsUETestCharacter();

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetRifle(UTP_WeaponComponent* InWeapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	float GetMaxHealth() const { return MaxHealth; }

	float GetHealth() const { return Health; }
	void Heal(float Amount);

	void PullPlayerName();

	FOnDeath& GetOnDeath() { return OnDeath; }
	FOnHealthChanged& GetOnHealthChanged() { return OnHealthChanged; }
	FOnPlayerNameChanged& GetOnPlayerNameChanged() { return OnPlayerNameChanged; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UFUNCTION(Server, Reliable)
	void ServerFire();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	const FString& GetPlayerName() const { return PlayerName; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void ApplyRegularDamage();

	void SetHealth(float InHealth);

	UFUNCTION()
	void OnCharacterDeath();

	UFUNCTION()
	void OnPlayerNameReplicated();

	UFUNCTION()
	void OnHealthReplicated();

	UFUNCTION(Client, Reliable)
	void ClientSetPlayerName();

	UFUNCTION(Server, Reliable)
	void ServerSetPlayerName(const FString& NewPlayerName);
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<UTP_WeaponComponent> Weapon;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UExistsUETestWidgetComponent> PlayerInformationWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	float RegularDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General", meta = (Tooltip = "In Seconds"))
	float RegularDamageInterval = 10.0f;

	UPROPERTY(Replicated, ReplicatedUsing = OnPlayerNameReplicated)
	FString PlayerName;

	UPROPERTY(Replicated, ReplicatedUsing = OnHealthReplicated)
	float Health;

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	FOnPlayerNameChanged OnPlayerNameChanged;

	FTimerHandle RegularDamageHandler;
};

