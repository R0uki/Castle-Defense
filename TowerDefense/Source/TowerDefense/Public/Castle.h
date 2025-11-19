// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Castle.generated.h"

// Delegate signature
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate, float, NewPercent);


UCLASS()
class TOWERDEFENSE_API ACastle : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* MainSound;

public:
	float MaxHealth = 1000;
	float Health = MaxHealth;
	
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnHealthUpdate OnHealthUpdate;
};
