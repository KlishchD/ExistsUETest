#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

UCLASS()
class EXISTSUETEST_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMenuGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
