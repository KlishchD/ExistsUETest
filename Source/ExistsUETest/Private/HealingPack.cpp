#include "HealingPack.h"

AHealingPack::AHealingPack()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickUpComponent"));
	PickUpComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	bReplicates = true;
}

void AHealingPack::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpComponent->GetOnPickUp().AddDynamic(this, &ThisClass::OnPickUp);
}

void AHealingPack::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	PickUpComponent->GetOnPickUp().RemoveAll(this);
	GetWorld()->GetTimerManager().ClearTimer(ReactivationTimerHandle);
}

void AHealingPack::OnPickUp(AExistsUETestCharacter* PickUpCharacter)
{
	float HealAmount = FMath::RandRange(MinHealthRegenerationAmount, MaxHealthRegenerationAmount);
	PickUpCharacter->Heal(HealAmount);

	float ReactivationRate = FMath::RandRange(MinReactivationTime, MaxReactivationTime);
	GetWorld()->GetTimerManager().SetTimer(ReactivationTimerHandle, this, &ThisClass::Reactivate, ReactivationRate);

	SetActorHiddenInGame(true);
}

void AHealingPack::Reactivate()
{
	PickUpComponent->Activate();
	SetActorHiddenInGame(false);
}

void AHealingPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

