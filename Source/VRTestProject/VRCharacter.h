// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "VRTestProjectGameInstance.h"
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
	//AddCharacterComponents
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
	//EndAddCharacterComponents

	UPROPERTY(replicatedUsing = OnRep_VRCharacterHMDStruct)
	FVRCharacterHMDStruct VRCharacterHMDStruct;
private:

	//Animations
	UPROPERTY()
	UHandAnimInstance* LeftHandAnimInstance;

	UPROPERTY()
	UHandAnimInstance* RightHandAnimInstance;

	//PickUps
	UPROPERTY()
	AActor* AttachedActorLeftHand;

	UPROPERTY()
	AActor* AttachedActorRightHand;

	//Inputs
	UPROPERTY()
	bool CanCharacterRotation = false;

	UPROPERTY()
	float MinRateForCharacterRotation = 0.3f;

	UPROPERTY()
	bool CanTryGrabLeft = true;

	UPROPERTY()
	bool CanTryGrabRight = true;

	UPROPERTY()
	bool CanTryTriggerRight = true;

	UPROPERTY()
	bool CanTryTriggerLeft = true;

	UPROPERTY()
	bool CanTryStopFireRight = false;

	UPROPERTY()
	bool CanTryStopFireLeft = false;

	//Health
	UPROPERTY()
	float MaxHealth = 100;

	UPROPERTY()
	float Health;

	//Widgets
	UPROPERTY()
	bool RightHandPointingAtWidget = false;

	UPROPERTY()
	bool LeftHandPointingAtWidget = false;

	//Weapon
	UPROPERTY()
	bool WeaponDropDelay = true;

	UPROPERTY()
	int32 LeftHandCurrentAmmoCountInWeapon = 0;

	UPROPERTY()
	int32 RightHandCurrentAmmoCountInWeapon = 0;


	UPROPERTY()
	FTimerHandle FTimerHandleWasTransitionBetweenLevels;

	UPROPERTY()
	UVRTestProjectGameInstance* CurrentGameInstance;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interfaces
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

	//Spline
	UFUNCTION()
	void UpdateSplineMesh(USplineComponent* SplineComponent, USplineMeshComponent* SplineMeshComponent);

	UFUNCTION()
	void SplineConstructionToWidget(UWidgetInteractionComponent* WidgetInteractionComponent, USplineComponent* SplineComponent, bool &HandPointingAtWidget);

	//
	UFUNCTION(BlueprintCallable, Category = "Interface")
	void CheckAndCallPickUpViaInterface(AActor* AttachedActorInHand, USceneComponent* AttachTo, FName SocketName);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);


	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_VRCharacterHMDStruct();

	UFUNCTION(Server, unreliable, WithValidation)
	void RepVRCharacterHMDStructFromClient(FVector VsRStruct);



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
	void DoFireAndStopFire(float &TriggerValue, bool &CanTryTrigger, AActor* AttachedActorHand, bool &CanTryStopFire, bool &HandPointingAtWidget);

	UFUNCTION()
	void ChooseToPressButtonOrShoot();


	UFUNCTION()
	void DoPressButtonOnWidget(float& TriggerValue , bool& CanTryTrigger);

	//SpawnCharacter
	UFUNCTION()
	void SpawnWeaponInHand(AActor* AttachedActorInHand, TEnumAsByte<LastWeaponInHand> &LastWeaponInHand, USkeletalMeshComponent* HandMesh, ASpawnManager* GameManagerRef);

	UFUNCTION()
	void DeadCharacter();

	UFUNCTION()
	void SetWasTransitionBetweenLevels();
};
