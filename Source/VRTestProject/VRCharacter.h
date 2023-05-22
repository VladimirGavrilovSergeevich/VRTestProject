// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MotionControllerComponent.h"
#include "VRCharacter.generated.h"

UCLASS()
class VRTESTPROJECT_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacter();

	    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* VRCamera;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand")
		USkeletalMeshComponent* HandMeshRight;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand")
		USkeletalMeshComponent* HandMeshLeft;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand")
		UMotionControllerComponent* MotionControllerRight;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand")
		UMotionControllerComponent* MotionControllerLeft;

		UPROPERTY()
		UAnimInstance* LeftHandAnimInstance;

		UPROPERTY()
		UAnimInstance* RightHandAnimInstance;
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Hand")
	USceneComponent* Center;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
