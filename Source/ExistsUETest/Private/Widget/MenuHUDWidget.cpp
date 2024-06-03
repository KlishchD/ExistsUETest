#include "Widget/MenuHUDWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Widget/SessionInformationWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ExistsUETestGameInstance.h"

void UMenuHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HostButton->OnClicked.AddDynamic(this, &ThisClass::OnHost);

	GameInstance = GetGameInstance<UExistsUETestGameInstance>();
	SessionSubsystem = GameInstance->GetSubsystem<USessionSubsystem>();

	SessionSubsystem->OnFindSessionsCompleteEvent.AddDynamic(this, &ThisClass::OnFindSessionsComplete);
	SessionSubsystem->OnJoinGameSessionCompleteEvent.AddDynamic(this, &ThisClass::OnJoinSessionComplete);

	for (int32 WidgetIndex = 0; WidgetIndex < MaxSearchResults; ++WidgetIndex)
	{
		USessionInformationWidget* Widget = CreateWidget<USessionInformationWidget>(this, SessionInformationWidgetClass);
		SessionsScrollBox->AddChild(Widget);
	}

	SessionSubsystem->FindSessions(MaxSearchResults, true);
}

void UMenuHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

	HostButton->OnClicked.RemoveAll(this);

	SessionSubsystem->OnFindSessionsCompleteEvent.RemoveAll(this);

	GetWorld()->GetTimerManager().ClearTimer(FindSessionTimerHandle);
}

void UMenuHUDWidget::OnHost()
{	
	FString PlayerName = PlayerNameTextBox->GetText().ToString();
	GameInstance->SetPlayerName(PlayerName);

	SessionSubsystem->CreateSession(MaxPlayerCount, true, GameMapName, PlayerName);
}

void UMenuHUDWidget::OnJoinSessionComplete(EBPOnJoinSessionCompleteResult Result)
{
	if (Result == EBPOnJoinSessionCompleteResult::Success)
	{
		FString PlayerName = PlayerNameTextBox->GetText().ToString();
		GameInstance->SetPlayerName(PlayerName);
	}
}

void UMenuHUDWidget::OnFindSessionsComplete(const TArray<FBlueprintSessionResult>& SessionsResult, bool Successful)
{
	for (UWidget* Widget : SessionsScrollBox->GetAllChildren())
	{
		if (USessionInformationWidget* InformationWidget = Cast<USessionInformationWidget>(Widget))
		{
			InformationWidget->RemoveSession();
		}
	}

	for (int32 SessionsResultIndex = 0; SessionsResultIndex < SessionsResult.Num(); ++SessionsResultIndex)
	{
		UWidget* CurrentWidget = SessionsScrollBox->GetChildAt(SessionsResultIndex);
		if (USessionInformationWidget* InformationWidget = Cast<USessionInformationWidget>(CurrentWidget))
		{
			InformationWidget->SetSession(SessionsResult[SessionsResultIndex]);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(FindSessionTimerHandle, [&]()
		{
			SessionSubsystem->FindSessions(MaxSearchResults, true);
		}, SearchDelayTimeSeconds, false);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Successful %d and found %d sessions"), Successful, SessionsResult.Num()));
}
