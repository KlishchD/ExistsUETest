#include "Widget/PlayerInformationWidget.h"
#include "ExistsUETestCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "ExistsUETestGameInstance.h"

void UPlayerInformationWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (Character)
	{
		Character->GetOnHealthChanged().RemoveAll(this);
		Character->GetOnPlayerNameChanged().RemoveAll(this);
	}
}

void UPlayerInformationWidget::SetCharacter(AExistsUETestCharacter* InCharacter)
{
	Character = InCharacter;

	if (Character)
	{
		Character->GetOnHealthChanged().AddUObject(this, &ThisClass::SetHealth);
		Character->GetOnPlayerNameChanged().AddUObject(this, &ThisClass::SetPlayerName);

		SetPlayerName(Character->GetPlayerName());
		SetHealth(Character->GetHealth());
	}
}

void UPlayerInformationWidget::SetHealth(float NewHealth)
{
	if (Character)
	{
		float Percent = NewHealth / Character->GetMaxHealth();
		HealthBar->SetPercent(Percent);
	}
}

void UPlayerInformationWidget::SetPlayerName(const FString& NewPlayerName)
{
	FText Name = FText::FromString(NewPlayerName);
	PlayerNameTextBlock->SetText(Name);
}
