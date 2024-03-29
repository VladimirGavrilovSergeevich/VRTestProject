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
#include "VRCharacter.generated.h"

USTRUCT(BlueprintType)
struct FVRCharacterHMDStruct
{
	GENERATED_BODY()

		//MotionControllerRight
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MotionControllerRightLocalLocation;

	    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator MotionControllerRightLocalRotation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMotionControllerComponent* MotionControllerRight;

		//MotionControllerLeft
	    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MotionControllerLeftLocalLocation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator MotionControllerLeftLocalRotation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMotionControllerComponent* MotionControllerLeft;

		//VRCamera
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector VRCameraLocalLocation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator VRCameraLocalRotation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* VRCamera;
};
UCLASS()
class VRTESTPROJECT_API AVRCharacter : public ACharacter, public IInteractionWithObjects
{
	GENERATED_BODY()

public:

	AVRCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interfaces IInteractionWithObjects
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	virtual void Drop() override;

	virtual void Fire() override;

	virtual void StopFire() override;

	virtual void LeftHandAmmoInWeapon(int32 AmmoCount) override;

	virtual void RightHandAmmoInWeapon(int32 AmmoCount) override;

	//Get
	UFUNCTION()
	float GetHealth() const;

	UFUNCTION()
	float GetMaxHealth() const;

	UFUNCTION()
	int32 GetLeftHandCurrentAmmoCountInWeapon();

	UFUNCTION()
	int32 GetRightHandCurrentAmmoCountInWeapon();

	UFUNCTION()
	AActor* GetAttachedActorLeftHand();

	UFUNCTION()
	AActor* GetAttachedActorRightHand();

	UFUNCTION(BlueprintCallable, Category = "GrabItem")
	AActor* GetGrabItemNearMotionController(UMotionControllerComponent* MotionController, USkeletalMeshComponent* HandMesh);

	//Spline WidgetInteract
	UFUNCTION()
	void UpdateSplineMesh(USplineComponent* SplineComponent, USplineMeshComponent* SplineMeshComponent);

	UFUNCTION()
	void SplineConstructionToWidget(UWidgetInteractionComponent* WidgetInteractionComponent, USplineComponent* SplineComponent, bool& HandPointingAtWidget);

	//replication
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_VRCharacterHMDStruct();

	UFUNCTION()
	void OnRep_GripLeftValueOnServer();

	UFUNCTION()
	void OnRep_GripRightValueOnServer();

	UFUNCTION()
	void OnRep_TriggerLeftValueOnServer();

	UFUNCTION()
	void OnRep_TriggerRightValueOnServer();

	UFUNCTION(Server, unreliable, WithValidation)
	void RepVRCharacterHMDStructFromClient(FVRCharacterHMDStruct HMDStruct);

	UFUNCTION(Server, reliable, WithValidation)
	void CallPickUpOrDropOnServerFromClientForLeftHand(float GripRate);

	UFUNCTION(Server, reliable, WithValidation)
	void CallPickUpOrDropOnServerFromClientForRightHand(float GripRate);

	UFUNCTION(Server, reliable, WithValidation)
	void CallDoFireAndStopFireOnServerFromClientForLeftHand(float TriggerValue);

	UFUNCTION(Server, reliable, WithValidation)
	void CallDoFireAndStopFireOnServerFromClientForRightHand(float TriggerValue);

	UFUNCTION(Server, reliable, WithValidation)
	void CallDeadCharacterOnServerFromClient();

	UFUNCTION(Server, reliable, WithValidation)
	void SetHealthCharacterOnServerFromClient(float NewHealth);

	UFUNCTION(Server, reliable, WithValidation)
	void LeftHandAmmoInWeaponOnServerFromClient(int32 NewAmmoCount);

	UFUNCTION(Server, reliable, WithValidation)
	void RightHandAmmoInWeaponOnServerFromClient(int32 NewAmmoCount);

	UFUNCTION(Server, unreliable, WithValidation)
	void SetGripLeftHandAnimValueOnServer(float GripLeftValue);

	UFUNCTION(Server, unreliable, WithValidation)
	void SetGripRightHandAnimValueOnServer(float GripRightValue);

	UFUNCTION(Server, unreliable, WithValidation)
	void SetTriggerLeftHandAnimValueOnServer(float TriggerLeftValue);

	UFUNCTION(Server, unreliable, WithValidation)
	void SetTriggerRightHandAnimValueOnServer(float TriggerRightValue);

	//
	UFUNCTION(BlueprintCallable, Category = "Interface")
	void CheckAndCallPickUpViaInterface(AActor* AttachedActorInHand, USceneComponent* AttachTo, FName SocketName);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	//AddCharacterComponents
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* VRCamera;

	UPROPERTY(EditAnywhere, replicated, BlueprintReadOnly, Category = "Hand")
	USkeletalMeshComponent* HandMeshRight;

	UPROPERTY(EditAnywhere, replicated, BlueprintReadOnly, Category = "Hand")
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
	//EndAddCharacterComponents

	//replication
	UPROPERTY(replicatedUsing = OnRep_VRCharacterHMDStruct)
	FVRCharacterHMDStruct VRCharacterHMDStruct;

	UPROPERTY(replicated)
	float Health;

	UPROPERTY(replicated)
	int32 LeftHandCurrentAmmoCountInWeapon = 0;

	UPROPERTY(replicated)
	int32 RightHandCurrentAmmoCountInWeapon = 0;
	UPROPERTY(replicatedUsing = OnRep_GripLeftValueOnServer)
	float GripLeftValueOnServer;

	UPROPERTY(replicatedUsing = OnRep_GripRightValueOnServer)
	float GripRightValueOnServer;

	UPROPERTY(replicatedUsing = OnRep_TriggerLeftValueOnServer)
	float TriggerLeftValueOnServer;

	UPROPERTY(replicatedUsing = OnRep_TriggerRightValueOnServer)
	float TriggerRightValueOnServer;

protected:
	virtual void BeginPlay() override;

private:

	//Input Hand
	UFUNCTION()
	void GripLeft(float Rate);

	UFUNCTION()
	void GripRight(float Rate);

	UFUNCTION()
	void TriggerLeft(float Rate);

	UFUNCTION()
	void TriggerRight(float Rate);

	//Input Move
	UFUNCTION()
	void MoveForward(float Val);

	UFUNCTION()
	void MoveRight(float Val);

	UFUNCTION()
	void CharacterRotation(float Rate);

	//Input WidgetInteraction
	UFUNCTION()
	void TriggerRightActionPressed();

	UFUNCTION()
	void TriggerRightActionReleased();

	UFUNCTION()
	void TriggerLeftActionPressed();

	UFUNCTION()
	void TriggerLeftActionReleased();

	//Input Fire or Widget
	UFUNCTION()
	void DoFireAndStopFire(float& TriggerValue, bool& CanTryTrigger, AActor* AttachedActorHand, bool& CanTryStopFire, bool& HandPointingAtWidget);

	UFUNCTION()
	void DoPressButtonOnWidget(float& TriggerValue, bool& CanTryTrigger);

	//DeadCharacter
	UFUNCTION()
	void DeadCharacter();

	//Animations
	UPROPERTY()
	UHandAnimInstance* LeftHandAnimInstance;

	UPROPERTY()
	UHandAnimInstance* RightHandAnimInstance;

	//PickUps
	UPROPERTY()
	AActor* AttachedActorLeftHand;

	UPROPERTY()
	AActor* TestAttachedActorLeftHand;

	UPROPERTY()
	AActor* AttachedActorRightHand;

	//Inputs
	bool CanCharacterRotation = false;

	const float MinRateForCharacterRotation = 0.3f;

	bool CanTryGrabLeft = true;

	bool CanTryGrabRight = true;

	bool CanTryTriggerRight = true;

	bool CanTryTriggerLeft = true;

	bool CanTryStopFireRight = false;

	bool CanTryStopFireLeft = false;

	//Health
	const float MaxHealth = 100;

	//Widgets
	bool RightHandPointingAtWidget = false;

	bool LeftHandPointingAtWidget = false;
};
