#include "Widget/ScoreBoardItemWidget.h"
#include "Components/TextBlock.h"
#include "Subsytems/ScoreSubsystem.h"

void UScoreBoardItemWidget::SetEntry(const FLogEntry& Entry)
{
	PlayerNameTextBlock->SetText(FText::FromString(Entry.PlayerName));
	ScoreTextBlock->SetText(FText::AsNumber(Entry.Score));
}
