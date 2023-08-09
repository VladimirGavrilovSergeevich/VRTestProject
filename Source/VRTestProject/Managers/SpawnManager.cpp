
#include "Managers/SpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnWeaponPoint.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	check(GetWorld());
}
void ASpawnManager::SpawnWeaponFromUI(WeaponInHand NameWeapon)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	auto CurrentSpawnWeaponPoint = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnWeaponPoint::StaticClass());

	switch (NameWeapon)
	{
	case None:
		break;
	case Pistol:
		GetWorld()->SpawnActor<APistol>(BP_Pistol, CurrentSpawnWeaponPoint->GetActorLocation(), CurrentSpawnWeaponPoint->GetActorRotation(), SpawnInfo);
		break;
	case Uzi:
		GetWorld()->SpawnActor<AUzi>(BP_Uzi, CurrentSpawnWeaponPoint->GetActorLocation(), CurrentSpawnWeaponPoint->GetActorRotation(), SpawnInfo);
		break;
	default:
		break;
	}
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

