// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/VRTestProjectPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/SpawnManager.h"


void AVRTestProjectPlayerController::CallSpawnPistolWeaponOnServerFromPlayerController_Implementation()
{
	auto SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	if (SpawnManager)
	{
		SpawnManager->SpawnWeaponFromUI(LastWeaponInHand::Pistol);
	}
}

bool AVRTestProjectPlayerController::CallSpawnPistolWeaponOnServerFromPlayerController_Validate()
{
	return true;
}

void AVRTestProjectPlayerController::CallSpawnUziWeaponOnServerFromPlayerController_Implementation()
{
	auto SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	if (SpawnManager)
	{
		SpawnManager->SpawnWeaponFromUI(LastWeaponInHand::Uzi);
	}
}

bool AVRTestProjectPlayerController::CallSpawnUziWeaponOnServerFromPlayerController_Validate()
{
	return true;
}
