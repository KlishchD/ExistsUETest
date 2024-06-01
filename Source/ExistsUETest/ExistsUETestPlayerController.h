#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExistsUETestPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class EXISTSUETEST_API AExistsUETestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;
};
