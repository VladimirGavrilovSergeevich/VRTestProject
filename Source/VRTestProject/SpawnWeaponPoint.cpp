

#include "SpawnWeaponPoint.h"


ASpawnWeaponPoint::ASpawnWeaponPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnWeaponPoint::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnWeaponPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

