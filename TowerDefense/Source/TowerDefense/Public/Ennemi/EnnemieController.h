// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnnemieController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnnemieController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

protected:
	virtual void BeginPlay() override;
	
public:
	AEnnemieController();
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* TreeAsset;
};
