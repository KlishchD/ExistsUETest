#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExistsUETestGameMode.generated.h"

UCLASS(minimalapi)
class AExistsUETestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AExistsUETestGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

};



