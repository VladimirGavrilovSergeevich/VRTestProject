// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VR_TestProjectGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchHasStarted);

UCLASS()
class VRTESTPROJECT_API AVR_TestProjectGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void HandleMatchHasStarted() override;

	UPROPERTY(BlueprintAssignable)
	FMatchHasStarted MatchHasStarted;
	
};
