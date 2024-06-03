#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUpActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPickUpActorStatusChanged, bool /* Status */);

class AExistsUETestCharacter;
class UTP_PickUpComponent;

UCLASS()
class EXISTSUETEST_API ABasePickUpActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABasePickUpActor();

	float GetMinReactivationTime() const { return MinReactivationTime; }
	float GetMaxReactivationTime() const { return MaxReactivationTime; }
	float GetReactivationChance() const { return ReactivationChance; }
	float GetReactivationAttemptDelay() const { return ReactivationAttemptDelay; }

	UFUNCTION(BlueprintCallable)
	virtual void ActivatePickUp();
	
	UFUNCTION(BlueprintCallable)
	virtual void DeactivatePickUp();

	FOnPickUpActorStatusChanged& GetOnStatusChanged() { return OnStatusChanged; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnPickUp(AExistsUETestCharacter* PickUpCharacter);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTP_PickUpComponent> PickUpComponent;

	UPROPERTY(EditAnywhere, Category = "Pick Up Parameters")
	float MinReactivationTime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Pick Up Parameters")
	float MaxReactivationTime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Pick Up Parameters")
	float ReactivationChance = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Pick Up Parameters")
	float ReactivationAttemptDelay = 0.5f;

	FOnPickUpActorStatusChanged OnStatusChanged;
};
