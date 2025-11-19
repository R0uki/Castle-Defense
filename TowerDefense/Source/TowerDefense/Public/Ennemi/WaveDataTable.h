// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UEnnemiesDataAsset.h"
#include "Engine/DataTable.h"
#include "WaveDataTable.generated.h"

USTRUCT(BlueprintType)
struct FWaveDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UEnnemiesDataAsset*> EnnemieData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> NbEnnemieToSpawnLocation;
};
