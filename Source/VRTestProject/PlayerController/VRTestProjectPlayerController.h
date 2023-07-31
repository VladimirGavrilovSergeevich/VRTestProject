// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VRTestProjectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API AVRTestProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, reliable, WithValidation)
	void CallSpawnPistolWeaponOnServerFromPlayerController();

	UFUNCTION(Server, reliable, WithValidation)
	void CallSpawnUziWeaponOnServerFromPlayerController();
	
};
