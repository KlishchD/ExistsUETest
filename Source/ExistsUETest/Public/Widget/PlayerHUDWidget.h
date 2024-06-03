#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UProgressBar;
class UScrollBox;
class UTextBlock;
class UButton;
class UScoreBoardItemWidget;
class UWidgetSwitcher;

UCLASS()
class EXISTSUETEST_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void SetHealth(float NewHealth);

	UFUNCTION()
	void OnDemonstrateTopScores(const TArray<FLogEntry>& Entries);

	UFUNCTION()
	void OnExit();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UScrollBox> ScorBoardScrollBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreBoardItemWidget> ScoreBoardItemWidgetClass;

	UPROPERTY(EditAnywhere)
	FText ScoreTextFormat;
};
