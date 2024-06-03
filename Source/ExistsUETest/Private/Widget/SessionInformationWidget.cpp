#include "Widget/SessionInformationWidget.h"
#include "Subsytems/SessionSubsystem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "FindSessionsCallbackProxy.h"

void USessionInformationWidget::SetSession(const FBlueprintSessionResult& InSession)
{
	Session = InSession;

	const FOnlineSession& SessionInfo = Session.OnlineResult.Session;
	const FOnlineSessionSettings& SessionSettings = SessionInfo.SessionSettings;

	FString SessionNameString;
	SessionSettings.Get(SETTING_SESSION_NAME, SessionNameString);

	FText SessionNameText = FText::FromString(SessionNameString);
	SessionNameTextBlock->SetText(SessionNameText);

	const int32 MaxPlayerCount = SessionSettings.NumPublicConnections;
	const int32 CurrentPlayerCount = MaxPlayerCount - SessionInfo.NumOpenPublicConnections;
	FText PlayersCountText = FText::Format(PlayersCountFormat, CurrentPlayerCount, MaxPlayerCount);
	PlayersCountTextBlock->SetText(PlayersCountText);

	SetVisibility(ESlateVisibility::Visible);
}

void USessionInformationWidget::RemoveSession()
{
	Session = FBlueprintSessionResult();
	SetVisibility(ESlateVisibility::Collapsed);
}

void USessionInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Collapsed);

	JoinSessionButton->OnClicked.AddDynamic(this, &ThisClass::OnJoin);
}

void USessionInformationWidget::NativeDestruct()
{
	Super::NativeDestruct();

	JoinSessionButton->OnClicked.RemoveAll(this);
}

void USessionInformationWidget::OnJoin()
{
	USessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<USessionSubsystem>();
	SessionSubsystem->JoinGameSession(Session);
}
