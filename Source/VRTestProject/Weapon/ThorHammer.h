// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "ThorHammer.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API AThorHammer : public AWeapon
{
	GENERATED_BODY()

public:

	AThorHammer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* GunMuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
	FName CurrentObjectSocketName = "ThorHammerSocket";

private:
	bool HammerFly = false;

	FVector StartActorLocation;

	USceneComponent* AttachToLocal;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;


	virtual void Drop() override;


	virtual void Fire() override;

	virtual void StopFire() override;

};