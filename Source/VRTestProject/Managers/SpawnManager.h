// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "VRCharacter.h"
#include "Weapon/Pistol.h"
#include "Weapon/Uzi.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UENUM()
enum WeaponInHand
{
	None,
	Pistol,
	Uzi
};

UCLASS()
class VRTESTPROJECT_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APistol> BP_Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUzi> BP_Uzi;

	UFUNCTION()
	void SpawnWeaponFromUI(WeaponInHand NameWeapon);

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
};
