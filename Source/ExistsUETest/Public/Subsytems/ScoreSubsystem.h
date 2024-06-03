#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Logging/LogMacros.h"
#include "ScoreSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ScoreSubsystemLog, Log, All)

class AExistsUETestCharacter;

USTRUCT()
struct EXISTSUETEST_API FLogEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString PlayerName;

	UPROPERTY(EditAnywhere)
	float Score;

};

bool operator<(const FLogEntry& EntryA, const FLogEntry& EntryB);

USTRUCT()
struct EXISTSUETEST_API FLogs
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FLogEntry> Entries;
};

UCLASS(Config = Game)
class EXISTSUETEST_API UScoreSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config)
	FString LogsFilePath = TEXT("Logs.json");

	UPROPERTY(EditAnywhere, Config)
	FString GameMapName = TEXT("FirstPersonMap");

	UPROPERTY(EditAnywhere, Config)
	float ScoreForPlayerKill = 10.0f;
	
	UPROPERTY(EditAnywhere, Config)
	float ScoreForPlayerHit = 1.0f;

	UPROPERTY(EditAnywhere, Config)
	int32 TopScoresDisplayCount = 10;
};

UCLASS()
class EXISTSUETEST_API UScoreSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddLogEntry(AExistsUETestCharacter* Player);

	TArray<FLogEntry> GetTopEntries();

protected:
	void OnPlayerKilled(AExistsUETestCharacter* KilledPlayer, AExistsUETestCharacter* KillerPlayer);
	void OnPlayerHit(AExistsUETestCharacter* ReceiverPlayer, AExistsUETestCharacter* HitterPlayer);

protected:
	UPROPERTY()
	const UScoreSubsystemSettings* Settings;

	UPROPERTY()
	FLogs Logs;

	bool LogsNeedSorting;
};
