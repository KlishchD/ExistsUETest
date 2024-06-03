#include "Subsytems/ScoreSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ExistsUETestDelegates.h"
#include "ExistsUETestCharacter.h"
#include "JsonObjectConverter.h"

DEFINE_LOG_CATEGORY(ScoreSubsystemLog);

bool UScoreSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (Outer->GetName() == GetDefault<UScoreSubsystemSettings>()->GameMapName)
	{
		return UKismetSystemLibrary::IsServer(Outer) && Super::ShouldCreateSubsystem(Outer);
	}

	return false;
}

void UScoreSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Settings = GetDefault<UScoreSubsystemSettings>();

	FExistsUETestDelegates::OnPlayerKilled.AddUObject(this, &ThisClass::OnPlayerKilled);
	FExistsUETestDelegates::OnPlayerHit.AddUObject(this, &ThisClass::OnPlayerHit);

	FString JsonString;
	if (FFileHelper::LoadFileToString(JsonString, *Settings->LogsFilePath))
	{
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &Logs))
		{
			UE_LOG(ScoreSubsystemLog, Warning, TEXT("Could not parse logs file"));
		}
	}
	else
	{
		UE_LOG(ScoreSubsystemLog, Warning, TEXT("Could not read logs file"));
	}
}

void UScoreSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FExistsUETestDelegates::OnPlayerKilled.RemoveAll(this);
	FExistsUETestDelegates::OnPlayerHit.RemoveAll(this);

	if (LogsNeedSorting)
	{
		Logs.Entries.Sort();
	}

	FString JsonString;
	if (FJsonObjectConverter::UStructToJsonObjectString(Logs, JsonString))
	{
		if (!FFileHelper::SaveStringToFile(JsonString, *Settings->LogsFilePath))
		{
			UE_LOG(ScoreSubsystemLog, Warning, TEXT("Could not save logs to file"));
		}
	}
	else
	{
		UE_LOG(ScoreSubsystemLog, Warning, TEXT("Could not convert logs into json"));
	}
}

void UScoreSubsystem::AddLogEntry(AExistsUETestCharacter* Player)
{
	Logs.Entries.Emplace(Player->GetPlayerName(), Player->GetScore());
	LogsNeedSorting = true;
}

TArray<FLogEntry> UScoreSubsystem::GetTopEntries()
{
	Logs.Entries.Sort(); // Sorting could be avoided by using std::multiset

	TArray<FLogEntry> Entries;

	int32 LowestScoreIndex = FMath::Max(0, Logs.Entries.Num() - Settings->TopScoresDisplayCount);
	for (int32 i = Logs.Entries.Num() - 1; i >= LowestScoreIndex; --i)
	{
		Entries.Add(Logs.Entries[i]);
	}

	return Entries;
}

void UScoreSubsystem::OnPlayerKilled(AExistsUETestCharacter* KilledPlayer, AExistsUETestCharacter* KillerPlayer)
{
	KillerPlayer->AddScore(Settings->ScoreForPlayerKill);
}

void UScoreSubsystem::OnPlayerHit(AExistsUETestCharacter* ReceiverPlayer, AExistsUETestCharacter* HitterPlayer)
{
	HitterPlayer->AddScore(Settings->ScoreForPlayerHit);
}

bool operator<(const FLogEntry& EntryA, const FLogEntry& EntryB)
{
	return EntryA.Score < EntryB.Score;
}
