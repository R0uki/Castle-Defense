// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FTowerLevelStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tower")
	UStaticMesh* TowerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tower")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tower")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tower")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tower")
	int UpdateAmount;
};


UCLASS()
class TOWERDEFENSE_API UTowerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTowerLevelStats> LevelStats;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* TowerSound;
};
