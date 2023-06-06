// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "VRCharacter.h"
#include "VRTestProjectGameInstance.h"
#include "Weapon/Pistol.h"
#include "Weapon/Uzi.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class VRTESTPROJECT_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnManager();

protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APistol> BP_Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUzi> BP_Uzi;

	UPROPERTY()
	AVRCharacter* CurrentPawn;

	UVRTestProjectGameInstance* CurrentGameInstance;

	UFUNCTION()
	AActor* SpawnWeapon(TEnumAsByte<LastWeaponInHand>& Weapon, FVector Location, FRotator Rotation);

	UFUNCTION()
	void ChoiceLastWeaponInHand();

	UFUNCTION()
	void ChoiceNowForLeftOrRightHand(AActor* Hand, TEnumAsByte<LastWeaponInHand>& LastWeaponInHand);

	UFUNCTION()
	void ClearValueOfWeaponInHand(TEnumAsByte<LastWeaponInHand>& Weapon);

	virtual void Tick(float DeltaTime) override;

};
