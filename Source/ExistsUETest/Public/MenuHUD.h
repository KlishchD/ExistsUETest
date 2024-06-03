#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class UMenuHUDWidget;

UCLASS()
class EXISTSUETEST_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuHUDWidget> MenuHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UMenuHUDWidget> MenuHUDWidget;
};
