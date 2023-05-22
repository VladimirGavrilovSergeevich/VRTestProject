// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HandAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API UHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Grip;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Trigger;
};
