#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_PickUpComponent.h"
#include "HealingPack.generated.h"

UCLASS()
class EXISTSUETEST_API AHealingPack : public AActor
{
	GENERATED_BODY()
	
public:	
	AHealingPack();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnPickUp(AExistsUETestCharacter* PickUpCharacter);

	void Reactivate();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTP_PickUpComponent> PickUpComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Healing")
	float MinHealthRegenerationAmount = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Healing")
	float MaxHealthRegenerationAmount = 100.0f;

	UPROPERTY(EditAnywhere, Category = "General")
	float MinReactivationTime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "General")
	float MaxReactivationTime = 10.0f;

	FTimerHandle ReactivationTimerHandle;
};
