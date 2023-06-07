
#include "Widget/SpawnWeapons.h"
#include "Managers/SpawnManager.h"
#include "Kismet/GameplayStatics.h"

void USpawnWeapons::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (SpawnWeaponPistolButton && SpawnWeaponUziButton)
	{
		SpawnWeaponPistolButton->OnReleased.AddDynamic(this, &USpawnWeapons::SpawnPistolWeapon);

		SpawnWeaponUziButton->OnReleased.AddDynamic(this, &USpawnWeapons::SpawnUziWeapon);
	}
}

void USpawnWeapons::SpawnPistolWeapon()
{
	auto SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	if (SpawnManager)
	{
		SpawnManager->SpawnWeaponFromUI(LastWeaponInHand::Pistol);
	}
}

void USpawnWeapons::SpawnUziWeapon()
{
	auto SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	if (SpawnManager)
	{
		SpawnManager->SpawnWeaponFromUI(LastWeaponInHand::Uzi);
	}
}
