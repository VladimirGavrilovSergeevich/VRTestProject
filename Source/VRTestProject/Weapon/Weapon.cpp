

#include "Weapon/Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PickUp(USceneComponent* AttachTo, FName SocketName)
{
}

void AWeapon::Drop()
{
}

void AWeapon::Fire()
{
}

void AWeapon::StopFire()
{
}

void AWeapon::LeftHandAmmoInWeapon(int32 AmmoCount)
{
}

void AWeapon::RightHandAmmoInWeapon(int32 AmmoCount)
{
}

