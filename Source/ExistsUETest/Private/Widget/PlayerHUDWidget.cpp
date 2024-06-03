#include "Widget/PlayerHUDWidget.h"
#include "ExistsUETestCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Widget/ScoreBoardItemWidget.h"
#include "ExistsUETestDelegates.h"
#include "Subsytems/ScoreSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AExistsUETestCharacter* Character = GetOwningPlayerPawn<AExistsUETestCharacter>())
	{
		Character->GetOnHealthChanged().AddUObject(this, &ThisClass::SetHealth);
	
		SetHealth(Character->GetHealth());
	}

	ExitButton->OnClicked.AddDynamic(this, &ThisClass::OnExit);

	FExistsUETestDelegates::OnDemonstrateTopScores.AddUObject(this, &ThisClass::OnDemonstrateTopScores);
}

void UPlayerHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (AExistsUETestCharacter* Character = GetOwningPlayerPawn<AExistsUETestCharacter>())
	{
		Character->GetOnHealthChanged().RemoveAll(this);
	}

	ExitButton->OnClicked.RemoveAll(this);
	FExistsUETestDelegates::OnDemonstrateTopScores.RemoveAll(this);
}

void UPlayerHUDWidget::SetHealth(float NewHealth)
{
	if (AExistsUETestCharacter* Character = GetOwningPlayerPawn<AExistsUETestCharacter>())
	{
		float Percent = NewHealth / Character->GetMaxHealth();
		HealthBar->SetPercent(Percent);
	}
}

void UPlayerHUDWidget::OnDemonstrateTopScores(const TArray<FLogEntry>& Entries)
{
	FText ScoreText = FText::Format(ScoreTextFormat, GetOwningPlayerPawn<AExistsUETestCharacter>()->GetScore());
	ScoreTextBlock->SetText(ScoreText);

	for (const FLogEntry& Entry : Entries)
	{
		UScoreBoardItemWidget* Widget = CreateWidget<UScoreBoardItemWidget>(this, ScoreBoardItemWidgetClass);
		Widget->SetEntry(Entry);
		ScorBoardScrollBox->AddChild(Widget);
	}

	WidgetSwitcher->SetActiveWidgetIndex(1);
}

void UPlayerHUDWidget::OnExit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
