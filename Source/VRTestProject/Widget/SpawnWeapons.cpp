
#include "Widget/SpawnWeapons.h"
#include "Managers/SpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/VRTestProjectPlayerController.h"

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
	auto CurrentPlayerController = Cast<AVRTestProjectPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CurrentPlayerController)
	{
		CurrentPlayerController->CallSpawnPistolWeaponOnServerFromPlayerController();
	}
}

void USpawnWeapons::SpawnUziWeapon()
{
	auto CurrentPlayerController = Cast<AVRTestProjectPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CurrentPlayerController)
	{
		CurrentPlayerController->CallSpawnUziWeaponOnServerFromPlayerController();
	}
}


