// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MapsSelection.h"
#include "Kismet/GameplayStatics.h"
#include "VRTestProjectGameInstance.h"
#include "VRCharacter.h"
#include "Weapon/Pistol.h"
#include "Weapon/Uzi.h"
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
	auto SpawnManager = Cast<ASpawnManager>(GetWorld()->GetGameInstance());
	SpawnManager->ChoiceLastWeaponInHand();
	/*auto CurrentGameInstance = Cast<UVRTestProjectGameInstance>(GetWorld()->GetGameInstance());
	if (CurrentGameInstance)
	{
	//	CurrentGameInstance->LastWeaponInLeftHand = LastWeaponInHand::None;
		auto CurrentPawn = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (CurrentPawn)
		{
			if (CurrentPawn->GetAttachedActorLeftHand())
			{
				if (CurrentPawn->GetAttachedActorLeftHand()->GetClass()->IsChildOf(APistol::StaticClass()))
			{
					CurrentGameInstance->LastWeaponInLeftHand = LastWeaponInHand::Pistol;
					CurrentGameInstance->WasTransitionBetweenLevels = true;
			}
			    else if (CurrentPawn->GetAttachedActorLeftHand()->GetClass()->IsChildOf(AUzi::StaticClass()))
				{
					CurrentGameInstance->LastWeaponInLeftHand = LastWeaponInHand::Uzi;
					CurrentGameInstance->WasTransitionBetweenLevels = true;
				}
				else
				{
					CurrentGameInstance->LastWeaponInLeftHand = LastWeaponInHand::None;
					CurrentGameInstance->WasTransitionBetweenLevels = false;
				}
				
			}
			else
			{
				CurrentGameInstance->LastWeaponInLeftHand = LastWeaponInHand::None;
				CurrentGameInstance->WasTransitionBetweenLevels = false;
			}
		}
		
	}*/
	if (UGameplayStatics::GetCurrentLevelName(this) == "MainMap")
	{
		UGameplayStatics::OpenLevel(this, "SecondMap");
	}
	else
	{
		UGameplayStatics::OpenLevel(this, "MainMap");
	}
}
