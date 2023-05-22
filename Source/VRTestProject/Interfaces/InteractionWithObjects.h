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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintNativeEvent)
	//void Test();

	UFUNCTION()
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) = 0;
};
