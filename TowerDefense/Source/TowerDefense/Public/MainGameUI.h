// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Framework/Styling/EditableTextBoxWidgetStyle.h"
#include "MainGameUI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMainGameUI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="References")
	class ACastle* CastleRef;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CastleHealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GoldNbr;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WaveNbr;
	
	UFUNCTION()
	void OnCastleHealthUpdate(float NewPercent);

	UFUNCTION()
	void OnNewGoldAmount(int NewGold);

	UFUNCTION()
	void OnUpdateNbWave(int Nb);
};
