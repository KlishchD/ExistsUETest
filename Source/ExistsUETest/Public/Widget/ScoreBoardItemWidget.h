#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreBoardItemWidget.generated.h"

struct FLogEntry;
class UTextBlock;

UCLASS()
class EXISTSUETEST_API UScoreBoardItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetEntry(const FLogEntry& Entry);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreTextBlock;
};
