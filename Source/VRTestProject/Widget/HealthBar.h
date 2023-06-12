// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VRCharacter.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"


UCLASS()
class VRTESTPROJECT_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	int AmmoCountForUI{0};

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable)
	int GetLeftHandAmmoCount();

	UFUNCTION(BlueprintCallable)
	int GetRightHandAmmoCount();
};
