// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenseGameMode.h"

#include "Castle.h"
#include "MainGameUI.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Ennemi/Ennemie.h"
#include "Kismet/GameplayStatics.h"


void ATowerDefenseGameMode::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnnemiInd.Init(0, 3);
	WaveData->GetAllRows("Get Wave Row", Rows);
	
	if (!CastleRef)
	{
		// Récupère le premier château trouvé dans la scène
		TArray<AActor*> FoundCastles;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACastle::StaticClass(), FoundCastles);

		if (FoundCastles.Num() > 0)
		{
			CastleRef = Cast<ACastle>(FoundCastles[0]);
			CastleRef->OnHealthUpdate.AddDynamic(this, &ATowerDefenseGameMode::IsGameOver);
		}
	}

	
	GetWorldTimerManager().SetTimer(NextWaveTimer,[this]()
	{
		StartWave(CurrentWave - 1);
	}, 3.f, true);
}

void ATowerDefenseGameMode::AddGold(int GoldToAdd)
{
	Gold += GoldToAdd;
	OnGoldUpdate.Broadcast(Gold);
}

void ATowerDefenseGameMode::RemoveGold(int GoldToRemove)
{
	Gold -= GoldToRemove;
	OnGoldUpdate.Broadcast(Gold);
}

int ATowerDefenseGameMode::GetGold()
{
	return Gold;
}

void ATowerDefenseGameMode::IsGameOver(float percent)
{
	if (percent <= 0)
	{
		UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), EndMenu);
		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
			UTextBlock* Text = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("Message")));
			if (Text)
				Text->SetText(FText::FromString("Votre Chateau est detruit, vous avez perdu."));
		}
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void ATowerDefenseGameMode::GameWin()
{
	UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), EndMenu);
	if (WidgetInstance)
	{
		WidgetInstance->AddToViewport();
		UTextBlock* Text = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("Message")));
		if (Text)
			Text->SetText(FText::FromString("Votre Chateau est encore en vie, vous avez Gagne."));
	}
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}


void ATowerDefenseGameMode::StartWave(int NumWave)
{
	GetWorldTimerManager().ClearTimer(NextWaveTimer);
	CurrentWaveTable = Rows[NumWave];
	OnNewWave.Broadcast(CurrentWave);
	
	for (int i = 0; i<3; i++)
	{
		CurrentEnnemiInd[i] = 0;
		CurrentNbWaveEnnemie += CurrentWaveTable->NbEnnemieToSpawnLocation[i];
	}

	//Spawn les ennemies
	for (int i = 0; i < CurrentWaveTable->SpawnLocation.Num() ; ++i)
	{
		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, [this, i]()
		{
			SpawnEnnemie(i);
		}, 1.f, true);

		SpawnTimer.Add(Timer);
	}
	
	CurrentWave++;
}

void ATowerDefenseGameMode::SpawnEnnemie(int IndLocation)
{
	if (CurrentEnnemiInd[IndLocation] < CurrentWaveTable->NbEnnemieToSpawnLocation[IndLocation])
	{
		//On créé le mob
		AEnnemie* NewEnnemi = GetWorld()->SpawnActor<AEnnemie>(EnnemieToSpawn, CurrentWaveTable->SpawnLocation[IndLocation], FRotator::ZeroRotator);
		if (NewEnnemi) //On lui donné les donnée
		{
			NewEnnemi->OnEnnemieDeath.AddDynamic(this, &ATowerDefenseGameMode::IsWaveFinish);
			CurrentEnnemiInd[IndLocation]++;
			NewEnnemi->InitEnnemieData(CurrentWaveTable->EnnemieData[FMath::RandRange(0,CurrentWaveTable->EnnemieData.Num()-1)]);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer[IndLocation]);
	}
}

void ATowerDefenseGameMode::IsWaveFinish(int GoldToAdd)
{
	CurrentNbWaveEnnemie --;
	if (GoldToAdd > 0)
		AddGold(GoldToAdd);

	if (CurrentNbWaveEnnemie == 0)
	{
		if (CurrentWave < 4)
		{
			GetWorldTimerManager().SetTimer(NextWaveTimer,[this]()
			{
				StartWave(CurrentWave - 1);
			}, 10.f, true);
		}
		else
		{
			GameWin();
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(NextWaveTimer);
	}
}

