#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUpActor.h"
#include "HealingPack.generated.h"

UCLASS()
class EXISTSUETEST_API AHealingPack : public ABasePickUpActor
{
	GENERATED_BODY()
	
public:	
	AHealingPack();

	virtual void ActivatePickUp() override;
	virtual void DeactivatePickUp() override;

protected:
	UFUNCTION()
	virtual void OnPickUp(AExistsUETestCharacter* PickUpCharacter) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Healing")
	float MinHealthRegenerationAmount = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Healing")
	float MaxHealthRegenerationAmount = 100.0f;
};
