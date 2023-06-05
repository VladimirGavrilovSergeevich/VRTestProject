// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VRTestProjectGameInstance.generated.h"

/**
 * 
 */
UENUM()
enum LastWeaponInHand
{
	None,
	Pistol,
	Uzi
};

UCLASS()
class VRTESTPROJECT_API UVRTestProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveAttachedActor")
	bool WasTransitionBetweenLevels = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveAttachedActor")
	TEnumAsByte<LastWeaponInHand> LastWeaponInLeftHand = LastWeaponInHand::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveAttachedActor")
	TEnumAsByte<LastWeaponInHand> LastWeaponInRightHand = LastWeaponInHand::None;
};
