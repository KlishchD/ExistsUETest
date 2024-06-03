#include "Subsytems/PickUpSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BasePickUpActor.h"

bool UPickUpSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return UKismetSystemLibrary::IsServer(Outer) && Super::ShouldCreateSubsystem(Outer);
}

void UPickUpSubsystem::RegisterPickUpActor(ABasePickUpActor* Actor)
{
	Actor->GetOnStatusChanged().AddUObject(this, &ThisClass::OnPickUpActorStatusChanged, Actor);
}

void UPickUpSubsystem::UnregisterPickUpActor(ABasePickUpActor* Actor)
{
	Actor->GetOnStatusChanged().RemoveAll(this);
}

void UPickUpSubsystem::OnPickUpActorStatusChanged(bool bStatus, ABasePickUpActor* Actor)
{
	if (!bStatus)
	{
		FTimerHandle FirstReactivationAttemptTimerHandle;
		float ReactivationRate = FMath::RandRange(Actor->GetMinReactivationTime(), Actor->GetMaxReactivationTime());
		GetWorld()->GetTimerManager().SetTimer(FirstReactivationAttemptTimerHandle, [this, Actor]()
			{
				ReactivationAttempt(Actor);
			}, ReactivationRate, false);
	}
}

void UPickUpSubsystem::ReactivationAttempt(ABasePickUpActor* Actor)
{
	float Value = FMath::RandRange(0.0f, 1.0f);
	if (Value <= Actor->GetReactivationChance())
	{
		Actor->ActivatePickUp();
	}
	else
	{
		FTimerHandle ReactivationTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ReactivationTimerHandle, [this, Actor]()
			{
				ReactivationAttempt(Actor);
			}, Actor->GetReactivationAttemptDelay(), false);
	}
}
