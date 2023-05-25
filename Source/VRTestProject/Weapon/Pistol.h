// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterBullet.h"
#include "Interfaces/InteractionWithObjects.h"
#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API APistol : public AWeapon, public IInteractionWithObjects
{
	GENERATED_BODY()

    public:
		APistol();
   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* GunMuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
	FName CurrentObjectSocketName{ "PistolSocket" };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacterBullet> BP_CharacterBullet;

	UFUNCTION()
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	UFUNCTION()
	virtual void Drop() override;

	UFUNCTION()
	virtual void Fire() override;
};
