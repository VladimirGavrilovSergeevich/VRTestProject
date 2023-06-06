// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MapsSelection.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/SpawnManager.h"

void UMapsSelection::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (LevelChangeButton)
	{
		LevelChangeButton->OnReleased.AddDynamic(this,&UMapsSelection::LevelChange);
	}
}

void UMapsSelection::LevelChange()
{
	auto SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	SpawnManager->ChoiceLastWeaponInHand();//remember the weapon in hand before changing the level
	
	if (UGameplayStatics::GetCurrentLevelName(this) == "MainMap")
	{
		UGameplayStatics::OpenLevel(this, "SecondMap");
	}
	else
	{
		UGameplayStatics::OpenLevel(this, "MainMap");
	}
}
