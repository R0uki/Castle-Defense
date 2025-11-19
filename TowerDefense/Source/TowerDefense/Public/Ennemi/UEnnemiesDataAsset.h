// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UEnnemiesDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEnnemiesDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	USkeletalMesh* EnnemieMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	int NbGold;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* DeathSound;
};
