// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UEnnemiesDataAsset.h"
#include "Ennemie.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnnemieDeath, int, gold);

UCLASS()
class TOWERDEFENSE_API AEnnemie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnnemie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	class UWidgetComponent* HealthBarWidget;

	virtual void EndPlay(const EEndPlayReason::Type r) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data")
	UEnnemiesDataAsset* EnnemieData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MaxHealth;

	void InitEnnemieData(UEnnemiesDataAsset* Data);
	float GetDamage() const;
	void ApplyDamage(float Damage);

	FOnEnnemieDeath OnEnnemieDeath;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
