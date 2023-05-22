// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "HandAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MotionControllerComponent.h"
#include "Interfaces/InteractionWithObjects.h"

#include "VRCharacter.generated.h"

UCLASS()
class VRTESTPROJECT_API AVRCharacter : public ACharacter, public IInteractionWithObjects
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
		UHandAnimInstance* LeftHandAnimInstance;

		UPROPERTY()
		UHandAnimInstance* RightHandAnimInstance;
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Hand")
	USceneComponent* Center;

	UPROPERTY()
	bool CanCharacterRotation;

	UPROPERTY()
	float MinRateForCharacterRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Hand")
	void GripLeft(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Hand")
	void GripRight(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Hand")
	void TriggerLeft(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Hand")
	void TriggerRight(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Hand")
	void MoveForward(float Val);

	UFUNCTION(BlueprintCallable, Category = "Hand")
	void MoveRight(float Val);

	UFUNCTION(BlueprintCallable, Category = "Hand")
	void CharacterRotation(float Rate);

	//void Test() override;
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	UFUNCTION(BlueprintCallable, Category = "Interface")
	void CheckInterface(AActor* TestActor, USceneComponent* AttachTo, FName SocketName);
};
