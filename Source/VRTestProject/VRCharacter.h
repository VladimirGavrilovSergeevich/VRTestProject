// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"
#include "HandAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MotionControllerComponent.h"
#include "Interfaces/InteractionWithObjects.h"
#include "Weapon/Pistol.h"
#include "Weapon/Uzi.h"
#include "VRCharacter.generated.h"

UCLASS()
class VRTESTPROJECT_API AVRCharacter : public ACharacter, public IInteractionWithObjects
{
	GENERATED_BODY()

public:
	AVRCharacter();

	    UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCameraComponent* VRCamera;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand")
		USkeletalMeshComponent* HandMeshRight;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand")
		USkeletalMeshComponent* HandMeshLeft;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand")
		UMotionControllerComponent* MotionControllerRight;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand")
		UMotionControllerComponent* MotionControllerLeft;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		UWidgetComponent* WidgetComponent;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		UWidgetInteractionComponent* WidgetInteractionComponentRight;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		UWidgetInteractionComponent* WidgetInteractionComponentLeft;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		USplineComponent* SplineComponentRight;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		USplineComponent* SplineComponentLeft;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		USplineMeshComponent* SplineMeshComponentRight;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		USplineMeshComponent* SplineMeshComponentLeft;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<APistol> BP_Pistol;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AUzi> BP_Uzi;
		
private:
	
	UPROPERTY()
	UHandAnimInstance* LeftHandAnimInstance;

	UPROPERTY()
	UHandAnimInstance* RightHandAnimInstance;

	UPROPERTY()
	bool CanCharacterRotation;

	UPROPERTY()
	float MinRateForCharacterRotation;

	UPROPERTY()
	bool CanTryGrabLeft;

	UPROPERTY()
	bool CanTryGrabRight;

	UPROPERTY()
	bool CanTryTriggerRight;

	UPROPERTY()
	bool CanTryTriggerLeft;

	UPROPERTY()
	bool CanTryStopFireRight;

	UPROPERTY()
	bool CanTryStopFireLeft;


	UPROPERTY()
	AActor* AttachedActorLeftHand;

	UPROPERTY()
	AActor* AttachedActorRightHand;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY()
	float Health;

	UPROPERTY()
	bool RightHandPointingAtWidget;

	UPROPERTY()
	bool LeftHandPointingAtWidget;

	UPROPERTY()
	FTimerHandle FTimerHandleWasTransitionBetweenLevels;

	

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	virtual void Drop() override;

	virtual void Fire() override;

	virtual void StopFire() override;

	float GetHealth() const;

	float GetMaxHealth() const;

	UFUNCTION()
	AActor* GetAttachedActorLeftHand();

	UFUNCTION()
	AActor* GetAttachedActorRightHand();

	UFUNCTION()
	void SetWasTransitionBetweenLevels();

	UFUNCTION()
	void UpdateSplineMesh(USplineComponent* SplineComponent, USplineMeshComponent* SplineMeshComponent);

	UFUNCTION()
	void SplineConstructionToWidget(UWidgetInteractionComponent* WidgetInteractionComponent, USplineComponent* SplineComponent, bool &HandPointingAtWidget);

	UFUNCTION(BlueprintCallable, Category = "Interface")
	void CheckAndCallPickUpViaInterface(AActor* TestActor, USceneComponent* AttachTo, FName SocketName);

	UFUNCTION(BlueprintCallable, Category = "GrabItem")
	AActor* GetGrabItemNearMotionController(UMotionControllerComponent* MotionController, USkeletalMeshComponent* HandMesh);

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

private:

	UFUNCTION(Category = "Hand")
	void GripLeft(float Rate);

	UFUNCTION(Category = "Hand")
	void GripRight(float Rate);

	UFUNCTION(Category = "Hand")
	void TriggerLeft(float Rate);

	UFUNCTION(Category = "Hand")
	void TriggerRight(float Rate);

	UFUNCTION(Category = "Move")
	void MoveForward(float Val);

	UFUNCTION(Category = "Move")
	void MoveRight(float Val);

	UFUNCTION(Category = "WidgetInteraction")
	void TriggerRightActionPressed();

	UFUNCTION(Category = "WidgetInteraction")
	void TriggerRightActionReleased();

	UFUNCTION(Category = "WidgetInteraction")
	void TriggerLeftActionPressed();

	UFUNCTION(Category = "WidgetInteraction")
	void TriggerLeftActionReleased();

	UFUNCTION(Category = "Move")
	void CharacterRotation(float Rate);

	UFUNCTION()
	void DoFireAndStopFire(float &TriggerValue, bool &CanTryTrigger, AActor* AttachedActorHand, bool &CanTryStopFire, bool &HandPointingAtWidget);

	UFUNCTION()
	void DoPressButtonOnWidget(float& TriggerValue , bool& CanTryTrigger);

	UFUNCTION()
	void ChooseToPressButtonOrShoot();


	
};
