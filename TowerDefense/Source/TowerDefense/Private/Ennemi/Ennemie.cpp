// Fill out your copyright notice in the Description page of Project Settings.


#include "Ennemi/Ennemie.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnnemie::AEnnemie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen); // fait face à la caméra
	HealthBarWidget->SetDrawSize(FVector2D(110.0f, 12.0f));
	HealthBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
}

// Called when the game starts or when spawned
void AEnnemie::BeginPlay()
{
	Super::BeginPlay();
}

void AEnnemie::EndPlay(const EEndPlayReason::Type r)
{
	if (Health <= 0 && EnnemieData)
		OnEnnemieDeath.Broadcast(EnnemieData->NbGold);
	else
		OnEnnemieDeath.Broadcast(0);

	Super::EndPlay(r);
}

// Called every frame
void AEnnemie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnnemie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnnemie::InitEnnemieData(UEnnemiesDataAsset* Data)
{
	EnnemieData = Data;
	
	GetCharacterMovement()->MaxWalkSpeed = EnnemieData->Speed;
	MaxHealth = EnnemieData->Health;
	Health = MaxHealth;
	GetMesh()->SetSkeletalMesh(EnnemieData->EnnemieMesh);
}

float AEnnemie::GetDamage() const
{
	return EnnemieData->Damage;
}

void AEnnemie::ApplyDamage(float Damage)
{
	Health -= Damage;
	
	if (Health <= 0)
	{
		SetLifeSpan(0.1f);
		if (EnnemieData->DeathSound)
			UGameplayStatics::PlaySound2D(GetWorld(), EnnemieData->DeathSound);
	}

	if (HealthBarWidget)
	{
		UUserWidget* Widget = HealthBarWidget->GetUserWidgetObject();
		if (Widget)
		{
			FName FunctionName = FName(TEXT("UpdateHealth"));
			Widget->CallFunctionByNameWithArguments(
				*FString::Printf(TEXT("%s %f"), *FunctionName.ToString(), Health / MaxHealth),
				*GLog, nullptr, true
			);
		}
	}
}



