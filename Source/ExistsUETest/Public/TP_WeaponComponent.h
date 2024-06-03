#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AExistsUETestCharacter;
class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXISTSUETEST_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UTP_WeaponComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Weapon")
	void ServerAttachWeapon(AExistsUETestCharacter* TargetCharacter);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon")
	void ServerFire();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticastFire();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticastAttachWeapon(AExistsUETestCharacter* TargetCharacter);

	UFUNCTION(Client, Reliable)
	void ClientAttachWeapon(AExistsUETestCharacter* TargetCharacter);

protected:
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AExistsUETestProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	TObjectPtr<USoundBase> FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TObjectPtr<UAnimMontage> FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(Replicated)
	TObjectPtr<AExistsUETestCharacter> Character;
};
