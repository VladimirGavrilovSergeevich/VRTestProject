
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
		//SpawnWeaponPistolButton->OnReleased.AddDynamic(this, &USpawnWeapons::TestSpawnPistolWeaponFromCharacter);

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
	//auto SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	//if (SpawnManager)
	//{
	//	SpawnManager->SpawnWeaponFromUI(LastWeaponInHand::Pistol);
	//}
}

void USpawnWeapons::SpawnUziWeapon()
{
	auto CurrentPlayerController = Cast<AVRTestProjectPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CurrentPlayerController)
	{
		CurrentPlayerController->CallSpawnUziWeaponOnServerFromPlayerController();
	}

	//auto SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	//if (SpawnManager)
	//{
	//	SpawnManager->SpawnWeaponFromUI(LastWeaponInHand::Uzi);
	//}
}

//void USpawnWeapons::TestSpawnPistolWeaponFromCharacter()
//{
//	auto CurrentPlayerController = Cast<AVRTestProjectPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//if (CurrentPlayerController)
//	{
//		CurrentPlayerController->CallSpawnPistolWeaponOnServerFromPlayerController();
//	}
//}

//void USpawnWeapons::CallSpawnPistolWeaponOnServerFromClient_Implementation()
//{
//	SpawnPistolWeapon();
//}

//bool USpawnWeapons::CallSpawnPistolWeaponOnServerFromClient_Validate()
//{
//	return true;
//}
