// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API APistol : public AWeapon
{
	GENERATED_BODY()

    public:
		APistol();
   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* GunMuzzle;
};
