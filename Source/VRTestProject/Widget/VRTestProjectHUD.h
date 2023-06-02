// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "HealthBar.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VRTestProjectHUD.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API AVRTestProjectHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UHealthBar> HealthBarWidget;
protected:
	virtual void BeginPlay() override;
};
