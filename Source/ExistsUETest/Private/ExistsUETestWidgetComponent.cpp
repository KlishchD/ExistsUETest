#include "ExistsUETestWidgetComponent.h"
#include "Kismet/GameplayStatics.h"

void UExistsUETestWidgetComponent::SetDisplayOnOwner(bool bInDiplayOnOwner)
{
	bDiplayOnOwner = bInDiplayOnOwner;
}

bool UExistsUETestWidgetComponent::DisplaysOnOwner() const
{
	return bDiplayOnOwner;
}

void UExistsUETestWidgetComponent::InitWidget()
{
	APlayerController* LocalPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (bDiplayOnOwner || !GetOwner()->IsOwnedBy(LocalPlayerController))
	{
		Super::InitWidget();
	}
}