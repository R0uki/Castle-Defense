// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include <string>

#include "DrawDebugHelpers.h"
#include "TowerDataAsset.h"
#include "TowerDefenseGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Ennemi/Ennemie.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DetectionArea = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionArea"));
	DetectionArea->SetupAttachment(RootComponent);

	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	TowerMesh->SetupAttachment(RootComponent);

	RangeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RangeMesh"));
	RangeMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ATower::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATower::OnOverlapEnd);
	
	TowerMesh->OnClicked.AddDynamic(this, &ATower::IfClicked);

	//Init des stat
	SetTowerStats(CurrentLevel - 1);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATower::UpdateTowerLevel()
{
	if (CurrentLevel < 2)
	{
		ATowerDefenseGameMode* GM = Cast<ATowerDefenseGameMode>(GetWorld()->GetAuthGameMode());
		int UpdateNbr = TowerData->LevelStats[CurrentLevel - 1].UpdateAmount;
		if (GM && GM->GetGold() >= UpdateNbr)
		{
			GM->RemoveGold(UpdateNbr);
			FlushPersistentDebugLines(GetWorld());

			CurrentLevel++;
			DrawDebugCircle(GetWorld(),GetActorLocation(), TowerData->LevelStats[CurrentLevel-1].Range, 32, FColor::Green, true, -1.f, 0,2.0f, FVector(1,0,0), FVector(0,1,0), false);
			SetTowerStats(CurrentLevel - 1);
		}
	}
}

void ATower::IfClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GameOver")));

	if (CurrentLevel >= 2)
		return;

	if (!TowerWidget)
	{
		TowerWidget = CreateWidget<UUserWidget>(GetWorld(), TowerWidgetClass);
		if (!TowerWidget)
			return;

		TowerWidget->AddToViewport();
		TowerWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (TowerWidget->IsVisible())
	{
		TowerWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TowerWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		// Récupérer le bouton
		if (UButton* Button = Cast<UButton>(TowerWidget->GetWidgetFromName(TEXT("UpgradeButton"))))
		{
			Button->OnClicked.AddDynamic(this, &ATower::UpdateTowerLevel);
		}

		if (UTextBlock* Cost = Cast<UTextBlock>(TowerWidget->GetWidgetFromName(TEXT("TowerCost"))))
		{
			Cost->SetText(FText::AsNumber(TowerData->LevelStats[CurrentLevel -1].UpdateAmount));
		}

		if (UTextBlock* Warning = Cast<UTextBlock>(TowerWidget->GetWidgetFromName(TEXT("Warning"))))
		{
			ATowerDefenseGameMode* GM = Cast<ATowerDefenseGameMode>(GetWorld()->GetAuthGameMode());
			if (GM->GetGold() >= TowerData->LevelStats[CurrentLevel -1].UpdateAmount)
				Warning->SetVisibility(ESlateVisibility::Hidden);
			else
				Warning->SetVisibility(ESlateVisibility::Visible);
		}
	}
}


void ATower::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor->IsA(AEnnemie::StaticClass()))
	{
		EnnemiesList.Add(Cast<AEnnemie>(OtherActor));
	}
}

void ATower::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor->IsA(AEnnemie::StaticClass()))
	{
		EnnemiesList.Remove(Cast<AEnnemie>(OtherActor));
	}
}

void ATower::TowerAttack()
{
	if (EnnemiesList.Num() != 0)
	{
		EnnemiesList[0]->ApplyDamage(TowerData->LevelStats[CurrentLevel -1].Damage);
		if(TowerData->TowerSound)
			UGameplayStatics::PlaySound2D(GetWorld(), TowerData->TowerSound);
	}
}

void ATower::SetTowerStats(int level)
{
	int ScaleRange = (TowerData->LevelStats[level].Range)/50;
	RangeMesh->SetWorldScale3D(FVector(1 * ScaleRange, 1* ScaleRange, 1* ScaleRange));
	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ATower::TowerAttack, TowerData->LevelStats[level].AttackSpeed, true);
	DetectionArea->SetSphereRadius(TowerData->LevelStats[level].Range);
	TowerMesh->SetStaticMesh(TowerData->LevelStats[level].TowerMesh);
}

