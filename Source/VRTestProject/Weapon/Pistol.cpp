// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Pistol.h"

APistol::APistol()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);

}

void APistol::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);
}

void APistol::Drop()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetSimulatePhysics(true);
}

void APistol::Fire()
{
	FVector LocationStartBullet = GunMuzzle->GetComponentLocation();
	FRotator RotationStartBullet = GunMuzzle->GetComponentRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ACharacterBullet>(BP_CharacterBullet,LocationStartBullet, RotationStartBullet, SpawnInfo);
}

void APistol::StopFire()
{
}
