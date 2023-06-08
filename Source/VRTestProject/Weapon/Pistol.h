// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterBullet.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
	FName CurrentObjectSocketName = "PistolSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacterBullet> BP_CharacterBullet;

	UPROPERTY()
	int32 MaxAmmoCount{8};

	UPROPERTY()
	int32 CurrentAmmoCount{MaxAmmoCount};

	UPROPERTY()
	UPrimitiveComponent* LastOverlapActorComp{nullptr};


	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	
	virtual void Drop() override;


	virtual void Fire() override;

	virtual void StopFire() override;

	UFUNCTION()
	bool AmmoCheck();

	UFUNCTION()
	void LoadAmmoIntoWeapon();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
