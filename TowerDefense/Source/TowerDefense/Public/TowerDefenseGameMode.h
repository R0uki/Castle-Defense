// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Castle.h"
#include "Ennemi/Ennemie.h"
#include "Ennemi/WaveDataTable.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldUpdate, int, NewGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewWave, int, NbWave);


UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* WaveData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TSubclassOf<AEnnemie> EnnemieToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> EndMenu;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Message;
	
	void StartWave(int NumWave);
	void SpawnEnnemie(int IndLocation);

	UFUNCTION()
	void IsWaveFinish(int Gold);

	int GetGold();
	void RemoveGold(int GoldToRemove);
	UFUNCTION()
	void IsGameOver(float percent);
	void GameWin();

	FOnGoldUpdate OnGoldUpdate;
	FOnNewWave OnNewWave;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AddGold(int GoldToAdd);


private:
	TArray<FWaveDataTable*> Rows;
	TArray<FTimerHandle> SpawnTimer;
	TArray<int> CurrentEnnemiInd;

	FWaveDataTable* CurrentWaveTable;
	FTimerHandle NextWaveTimer;
	ACastle* CastleRef;

	int CurrentNbWaveEnnemie;
	int CurrentWave = 1;
	int Gold = 0;
};
