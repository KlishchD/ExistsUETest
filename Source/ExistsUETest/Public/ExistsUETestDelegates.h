#pragma once

#include "CoreMinimal.h"

class AExistsUETestCharacter;
struct FLogEntry;

class EXISTSUETEST_API FExistsUETestDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerKilled, AExistsUETestCharacter* /* Killed Player */, AExistsUETestCharacter* /* Killer Player */);
	static FOnPlayerKilled OnPlayerKilled;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerHit, AExistsUETestCharacter* /* Receiver Player */, AExistsUETestCharacter* /* Hitter Player */);
	static FOnPlayerHit OnPlayerHit;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDemonstrateTopScores, const TArray<FLogEntry>&);
	static FOnDemonstrateTopScores OnDemonstrateTopScores;
};
