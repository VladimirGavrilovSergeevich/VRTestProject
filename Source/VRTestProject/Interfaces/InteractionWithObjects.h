// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionWithObjects.generated.h"

UINTERFACE(MinimalAPI)
class UInteractionWithObjects : public UInterface
{
	GENERATED_BODY()
};


class VRTESTPROJECT_API IInteractionWithObjects
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) = 0;

	UFUNCTION()
	virtual void Drop() = 0;

	UFUNCTION()
	virtual void Fire() = 0;

	UFUNCTION()
	virtual void StopFire() = 0;

	UFUNCTION()
	virtual void LeftHandAmmoInWeapon(int32 AmmoCount) = 0;

	UFUNCTION()
	virtual void RightHandAmmoInWeapon(int32 AmmoCount) = 0;

	UFUNCTION()
	virtual void PickUpOnServer(USceneComponent* AttachTo, FName SocketName) = 0;

};
