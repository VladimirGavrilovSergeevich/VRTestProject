

#include "Weapon/Pistol.h"

APistol::APistol()
	
{
	CurrentObjectSocketName = "PistolSocket";
	MaxAmmoCount = 8;
	CurrentAmmoCount = MaxAmmoCount;
}

void APistol::Fire()
{
	if (AmmoCheck())
	{
		FVector LocationStartBullet = GunMuzzle->GetComponentLocation();
		FRotator RotationStartBullet = GunMuzzle->GetComponentRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ACharacterBullet>(BP_CharacterBullet, LocationStartBullet, RotationStartBullet, SpawnInfo);

		SendCountHandAmmoInWeapon(CurrentAmmoCount);
	}
}

void APistol::Drop()
{
	StopFire();
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetSimulatePhysics(true);

	SendCountHandAmmoInWeapon(0);

	WeaponAttachToHandNow = nullptr;
}



