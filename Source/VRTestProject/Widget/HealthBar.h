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

	UFUNCTION(BlueprintCallable)
		float GetHealth();
protected:
	
};
