// Fill out your copyright notice in the Description page of Project Settings.


#include "Ennemi/EnnemieController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnnemieController::BeginPlay()
{
	Super::BeginPlay();
}

AEnnemieController::AEnnemieController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AEnnemieController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (TreeAsset && TreeAsset->BlackboardAsset) {
		// Run the behavior tree
		RunBehaviorTree(TreeAsset);
		
		// Initialize the blackboard with the blackboard asset
		BlackboardComponent->InitializeBlackboard(*TreeAsset->BlackboardAsset);
	}
}
