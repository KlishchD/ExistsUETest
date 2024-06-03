#include "TP_PickUpComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UTP_PickUpComponent::UTP_PickUpComponent()
{
	SphereRadius = 32.f;

	SetIsReplicatedByDefault(true);
}

void UTP_PickUpComponent::ActivatePickUp()
{
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::DeactivatePickUp()
{
	OnComponentBeginOverlap.RemoveAll(this);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AExistsUETestCharacter* Character = Cast<AExistsUETestCharacter>(OtherActor);
	if(Character != nullptr)
	{
		OnPickUp.Broadcast(Character);

		DeactivatePickUp();
	}
}
