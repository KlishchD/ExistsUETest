#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInformationWidget.generated.h"

class UProgressBar;
class UTextBlock;
class AExistsUETestCharacter;

UCLASS()
class EXISTSUETEST_API UPlayerInformationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetCharacter(AExistsUETestCharacter* InCharacter);

protected:
	virtual void NativeDestruct() override;

	UFUNCTION()
	void SetHealth(float NewHealth);

	UFUNCTION()
	void SetPlayerName(const FString& NewPlayerName);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY()
	TObjectPtr<AExistsUETestCharacter> Character;
};
