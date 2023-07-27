

#include "PickUpItems/BasePickUpObject.h"

ABasePickUpObject::ABasePickUpObject()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);
}


void ABasePickUpObject::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABasePickUpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickUpObject::PickUp(USceneComponent* AttachTo, FName SocketName)
{
}

void ABasePickUpObject::Drop()
{
}

void ABasePickUpObject::Fire()
{
}

void ABasePickUpObject::StopFire()
{
}

void ABasePickUpObject::LeftHandAmmoInWeapon(int32 AmmoCount)
{
}

void ABasePickUpObject::RightHandAmmoInWeapon(int32 AmmoCount)
{
}

void ABasePickUpObject::PickUpOnServer_Implementation(USceneComponent* AttachTo, FName SocketName)
{
	PickUp(AttachTo,SocketName);
}

bool ABasePickUpObject::PickUpOnServer_Validate(USceneComponent* AttachTo, FName SocketName)
{
	return true;
}

