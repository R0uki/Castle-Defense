// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameUI.h"

#include <string>

#include "Castle.h"
#include "TowerDefenseGameMode.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMainGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CastleRef)
	{
		// Récupère le premier château trouvé dans la scène
		TArray<AActor*> FoundCastles;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACastle::StaticClass(), FoundCastles);

		if (FoundCastles.Num() > 0)
		{
			CastleRef = Cast<ACastle>(FoundCastles[0]);
		}
	}

	

	// Si on a bien trouvé le château -> bind le délégué
	if (CastleRef)
	{
		CastleRef->OnHealthUpdate.AddDynamic(this, &UMainGameUI::OnCastleHealthUpdate);
	}

	ATowerDefenseGameMode* GM = Cast<ATowerDefenseGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->OnGoldUpdate.AddDynamic(this, &UMainGameUI::OnNewGoldAmount);
		GM->OnNewWave.AddDynamic(this, &UMainGameUI::OnUpdateNbWave);
	}

}

void UMainGameUI::OnCastleHealthUpdate(float NewPercent)
{
	if (CastleHealthBar)
		CastleHealthBar->SetPercent(NewPercent);
}

void UMainGameUI::OnNewGoldAmount(int NewGold)
{
	GoldNbr->SetText(FText::AsNumber(NewGold));
}

void UMainGameUI::OnUpdateNbWave(int Nb)
{
	WaveNbr->SetText(FText::AsNumber(Nb));
}
