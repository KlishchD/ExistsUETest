#include "MenuGameMode.h"

AMenuGameMode::AMenuGameMode()
{
}

void AMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NewPlayer->SetInputMode(FInputModeUIOnly());
	NewPlayer->SetShowMouseCursor(true);
}

void AMenuGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (APlayerController* Player = Cast<APlayerController>(Exiting))
	{
		Player->SetInputMode(FInputModeGameOnly());
		Player->SetShowMouseCursor(false);
	}
}
