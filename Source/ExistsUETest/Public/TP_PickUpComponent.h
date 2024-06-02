#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ExistsUETestCharacter.h"
#include "TP_PickUpComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AExistsUETestCharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXISTSUETEST_API UTP_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UTP_PickUpComponent();

	void Activate();
	void Deactivate();

	FOnPickUp& GetOnPickUp() { return OnPickUp; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickUp;
};