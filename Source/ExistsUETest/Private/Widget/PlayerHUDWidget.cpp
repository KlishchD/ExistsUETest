#include "Widget/PlayerHUDWidget.h"
#include "ExistsUETestCharacter.h"
#include "Components/ProgressBar.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AExistsUETestCharacter* Character = GetOwningPlayerPawn<AExistsUETestCharacter>())
	{
		Character->GetOnHealthChanged().AddUObject(this, &ThisClass::SetHealth);
	
		SetHealth(Character->GetHealth());
	}
}

void UPlayerHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (AExistsUETestCharacter* Character = GetOwningPlayerPawn<AExistsUETestCharacter>())
	{
		Character->GetOnHealthChanged().RemoveAll(this);
	}
}

void UPlayerHUDWidget::SetHealth(float NewHealth)
{
	if (AExistsUETestCharacter* Character = GetOwningPlayerPawn<AExistsUETestCharacter>())
	{
		float Percent = NewHealth / Character->GetMaxHealth();
		HealthBar->SetPercent(Percent);
	}
}
