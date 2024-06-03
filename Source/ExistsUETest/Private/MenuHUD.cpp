#include "MenuHUD.h"
#include "Widget/MenuHUDWidget.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	MenuHUDWidget = CreateWidget<UMenuHUDWidget>(GetOwningPlayerController(), MenuHUDWidgetClass);
	MenuHUDWidget->AddToViewport();
}

void AMenuHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	MenuHUDWidget->RemoveFromParent();
}
