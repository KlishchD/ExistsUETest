// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExistsUETestGameInstance.generated.h"

UCLASS()
class EXISTSUETEST_API UExistsUETestGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void SetPlayerName(const FString& Name);
	const FString& GetPlayerName() const;

protected:
	FString PlayerName;
};
