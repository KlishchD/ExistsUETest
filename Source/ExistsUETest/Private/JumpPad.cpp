#include "JumpPad.h"
#include "ExistsUETestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AJumpPad::AJumpPad()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AJumpPad::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void AJumpPad::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	MeshComponent->OnComponentBeginOverlap.RemoveAll(this);
}

void AJumpPad::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AExistsUETestCharacter* Chraracter = Cast<AExistsUETestCharacter>(OtherActor))
	{
		UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(Chraracter->GetMovementComponent());
		MovementComponent->Velocity.Z = 0.0f;
		MovementComponent->AddImpulse(FVector3d::UpVector * UpwardsImpuls, true);
	}
}

void AJumpPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

