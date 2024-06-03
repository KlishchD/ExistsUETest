#include "AExistsUETestHUD.h"
#include "Widget/PlayerHUDWidget.h"

AExistsUETestHUD::AExistsUETestHUD()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AExistsUETestHUD::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UPlayerHUDWidget>(GetOwningPlayerController(), HUDWidgetClass);
	HUDWidget->AddToViewport();
}

void AExistsUETestHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
