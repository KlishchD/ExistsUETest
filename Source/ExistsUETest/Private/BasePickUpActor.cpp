#include "BasePickUpActor.h"
#include "TP_PickUpComponent.h"
#include "Subsytems/PickUpSubsystem.h"

ABasePickUpActor::ABasePickUpActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickUpComponent"));
	PickUpComponent->SetupAttachment(RootComponent);

	bReplicates = true;
}

void ABasePickUpActor::ActivatePickUp()
{
	OnStatusChanged.Broadcast(true);
	PickUpComponent->ActivatePickUp();

	PickUpComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ABasePickUpActor::DeactivatePickUp()
{
	OnStatusChanged.Broadcast(false);
	PickUpComponent->DeactivatePickUp();

	PickUpComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ABasePickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpComponent->GetOnPickUp().AddDynamic(this, &ThisClass::OnPickUp);

	if (UPickUpSubsystem* PickUpSubsytem = GetWorld()->GetSubsystem<UPickUpSubsystem>())
	{
		PickUpSubsytem->RegisterPickUpActor(this);
		ActivatePickUp();
	}
}

void ABasePickUpActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	PickUpComponent->GetOnPickUp().RemoveAll(this);

	if (UPickUpSubsystem* PickUpSubsytem = GetWorld()->GetSubsystem<UPickUpSubsystem>())
	{
		PickUpSubsytem->UnregisterPickUpActor(this);
	}
}

void ABasePickUpActor::OnPickUp(AExistsUETestCharacter* PickUpCharacter)
{
	DeactivatePickUp();
}
