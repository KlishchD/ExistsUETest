#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PickUpSubsystem.generated.h"

class ABasePickUpActor;

UCLASS()
class EXISTSUETEST_API UPickUpSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void RegisterPickUpActor(ABasePickUpActor* Actor);
	void UnregisterPickUpActor(ABasePickUpActor* Actor);

protected:
	void OnPickUpActorStatusChanged(bool bStatus, ABasePickUpActor* Actor);
	void ReactivationAttempt(ABasePickUpActor* Actor);
};
