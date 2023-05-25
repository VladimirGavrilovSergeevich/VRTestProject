// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Pistol.h"

APistol::APistol()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);
}

void APistol::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);
	UE_LOG(LogTemp, Warning, TEXT("PickUpPistol"));
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
	//FVector ScaleStartBullet{ 0.1f,0.1f,0.1f };
	//FVector Scale3D(0.1f);
	//FTransform TransformForSpawnBullet;
	//TransformForSpawnBullet(Scale3D(0.1f)); //= FTransform(LocationStartBullet ,RotationStartBullet, FVector Scale3D(0.1f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//GetWorld()->SpawnActor<ACharacterBullet>()

	GetWorld()->SpawnActor<ACharacterBullet>(BP_CharacterBullet,LocationStartBullet, RotationStartBullet, SpawnInfo);
}
