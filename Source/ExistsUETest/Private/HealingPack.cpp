#include "HealingPack.h"
#include "ExistsUETestCharacter.h"

AHealingPack::AHealingPack()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void AHealingPack::ActivatePickUp()
{
	Super::ActivatePickUp();

	SetActorHiddenInGame(false);
}

void AHealingPack::DeactivatePickUp()
{
	Super::DeactivatePickUp();

	SetActorHiddenInGame(true);
}

void AHealingPack::OnPickUp(AExistsUETestCharacter* PickUpCharacter)
{
	Super::OnPickUp(PickUpCharacter);

	float HealAmount = FMath::RandRange(MinHealthRegenerationAmount, MaxHealthRegenerationAmount);
	PickUpCharacter->Heal(HealAmount);
}
