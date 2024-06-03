#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuHUDWidget.generated.h"

class USessionInformationWidget;
class UExistsUETestGameInstance;
class USessionSubsystem;
class UEditableTextBox;
class UButton;
class UScrollBox;

UCLASS()
class EXISTSUETEST_API UMenuHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnHost();

	UFUNCTION()
	void OnJoinSessionComplete(EBPOnJoinSessionCompleteResult Result);

	UFUNCTION()
	void OnFindSessionsComplete(const TArray<FBlueprintSessionResult>& SessionsResult, bool Successful);
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> PlayerNameTextBox;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> HostButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UScrollBox> SessionsScrollBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USessionInformationWidget> SessionInformationWidgetClass;

	UPROPERTY(EditAnywhere)
	FString GameMapName;

	UPROPERTY()
	TObjectPtr<UExistsUETestGameInstance> GameInstance;

	UPROPERTY()
	TObjectPtr<USessionSubsystem> SessionSubsystem;

	const int32 MaxPlayerCount = 10;
	const int32 MaxSearchResults = 10;
	const float SearchDelayTimeSeconds = 1.0f;

	FTimerHandle FindSessionTimerHandle;
};
