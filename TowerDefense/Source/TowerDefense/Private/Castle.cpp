// Fill out your copyright notice in the Description page of Project Settings.


#include "Castle.h"

#include "Blueprint/UserWidget.h"
#include "Ennemi/Ennemie.h"
#include "Kismet/GameplayStatics.h"

void ACastle::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACastle::OnOverlapBegin);

	if (MainSound) {

		UGameplayStatics::PlaySound2D( GetWorld(), MainSound);
	}
}

void ACastle::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
		if (OtherActor->IsA(AEnnemie::StaticClass()))
		{
			AEnnemie* Ennemi = Cast<AEnnemie>(OtherActor);
			Health = Health - Ennemi->GetDamage();
			OtherActor->Destroy();

			OnHealthUpdate.Broadcast(Health/MaxHealth);
		}
}