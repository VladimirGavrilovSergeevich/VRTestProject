

#include "Weapon/Uzi.h"

AUzi::AUzi()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.UpdateTickIntervalAndCoolDown(0.05);
	CurrentObjectSocketName = "UziSocket";
	MaxAmmoCount = 100;
    CurrentAmmoCount = MaxAmmoCount;

}

void AUzi::Tick(float DeltaTime)
{
	if (BurstFire)
	{
		Fire();
	}
}

void AUzi::Fire()
{
	if (AmmoCheck())
	{
		FVector LocationStartBullet = GunMuzzle->GetComponentLocation();
		FRotator RotationStartBullet = GunMuzzle->GetComponentRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ACharacterBullet>(BP_CharacterBullet, LocationStartBullet, RotationStartBullet, SpawnInfo);
		BurstFire = true;

		SendCountHandAmmoInWeapon(CurrentAmmoCount);
	}
}

void AUzi::StopFire()
{
	BurstFire = false;
}



