#include "ExistsUETestGameInstance.h"

void UExistsUETestGameInstance::SetPlayerName(const FString& Name)
{
	PlayerName = Name;
}

const FString& UExistsUETestGameInstance::GetPlayerName() const
{
	return PlayerName;
}
