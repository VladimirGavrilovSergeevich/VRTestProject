// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Uzi.h"

AUzi::AUzi()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);
}

void AUzi::Tick(float DeltaTime)
{
	if (BurstFire)
	{
		Fire();
	}
}

void AUzi::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);
}

void AUzi::Drop()
{
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	StaticMesh->SetSimulatePhysics(true);
}

void AUzi::Fire()
{
	FVector LocationStartBullet = GunMuzzle->GetComponentLocation();
	FRotator RotationStartBullet = GunMuzzle->GetComponentRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ACharacterBullet>(BP_CharacterBullet, LocationStartBullet, RotationStartBullet, SpawnInfo);
	BurstFire = true;
}

void AUzi::StopFire()
{
	BurstFire = false;
}
