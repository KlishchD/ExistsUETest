#include "ExistsUETestGameMode.h"
#include "ExistsUETestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AExistsUETestGameMode::AExistsUETestGameMode() : Super()
{
}

void AExistsUETestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NewPlayer->GetPawn<AExistsUETestCharacter>()->PullPlayerName();
}
