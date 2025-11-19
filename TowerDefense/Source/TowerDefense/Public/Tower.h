// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Ennemi/Ennemie.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class TOWERDEFENSE_API ATower : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	class USphereComponent* DetectionArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	class UStaticMeshComponent* TowerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	class UStaticMeshComponent* RangeMesh;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> TowerWidgetClass;

	
	
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	class UTowerDataAsset* TowerData;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Tower")
	void UpdateTowerLevel();

	UFUNCTION()
	void IfClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	
private:
	int CurrentLevel = 1;
	TArray<AEnnemie*> EnnemiesList;
	FTimerHandle TimerHandle_Attack;
	
	void TowerAttack();
	void SetTowerStats(int level);
	bool bShowRange = false;

	UPROPERTY()
	UUserWidget* TowerWidget;
};
