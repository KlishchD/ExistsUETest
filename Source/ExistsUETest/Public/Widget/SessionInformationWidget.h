#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsytems/SessionSubsystem.h"
#include "SessionInformationWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class EXISTSUETEST_API USessionInformationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetSession(const FBlueprintSessionResult& InSession);
	void RemoveSession();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnJoin();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> SessionNameTextBlock;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayersCountTextBlock;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> JoinSessionButton;

	UPROPERTY(EditAnywhere)
	FText PlayersCountFormat;

	FBlueprintSessionResult Session;
};
