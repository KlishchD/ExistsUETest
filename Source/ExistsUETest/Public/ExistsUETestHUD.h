#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExistsUETestHUD.generated.h"

class UPlayerHUDWidget;
struct FLogEntry;

UCLASS()
class EXISTSUETEST_API AExistsUETestHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AExistsUETestHUD();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerHUDWidget> HUDWidget;
};
