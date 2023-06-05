// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/SpawnManager.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameInstance = Cast<UVRTestProjectGameInstance>(GetWorld()->GetGameInstance());
	check(CurrentGameInstance);
	CurrentPawn = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	check(CurrentPawn);
}

AActor* ASpawnManager::SpawnWeapon(LastWeaponInHand Weapon, FVector Location, FRotator Rotation)
{

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		switch (Weapon)

		{
		case::LastWeaponInHand::None:

			break;

	    case::LastWeaponInHand::Pistol:
	        GetWorld()->SpawnActor<APistol>(BP_Pistol, Location, Rotation, SpawnInfo);
	        break;

		case::LastWeaponInHand::Uzi:
			GetWorld()->SpawnActor<AUzi>(BP_Uzi, Location, Rotation, SpawnInfo);
			break;

		default:
			break;
		}

	return nullptr;
}

void ASpawnManager::ChoiceLastWeaponInHand()
{
	CurrentPawn = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (IsValid(CurrentPawn->GetAttachedActorLeftHand()))
	{
		ChoiceNowForLeftOrRightHand(CurrentPawn->GetAttachedActorLeftHand(), CurrentGameInstance->LastWeaponInLeftHand);
	}
	if (IsValid(CurrentPawn->GetAttachedActorRightHand()))
	{
		ChoiceNowForLeftOrRightHand(CurrentPawn->GetAttachedActorRightHand(), CurrentGameInstance->LastWeaponInRightHand);
	}
			
			
			
}

void ASpawnManager::ChoiceNowForLeftOrRightHand(AActor* Hand, TEnumAsByte<LastWeaponInHand>& LastWeaponInHand)
{
	if (Hand)
	{
		if (Hand->GetClass()->IsChildOf(APistol::StaticClass()))
		{
			LastWeaponInHand = LastWeaponInHand::Pistol;
			CurrentGameInstance->WasTransitionBetweenLevels = true;
		}
		else if (Hand->GetClass()->IsChildOf(AUzi::StaticClass()))
		{
			LastWeaponInHand = LastWeaponInHand::Uzi;
			CurrentGameInstance->WasTransitionBetweenLevels = true;
		}
		else
		{
			LastWeaponInHand = LastWeaponInHand::None;
			CurrentGameInstance->WasTransitionBetweenLevels = false;
		}
	}
}

	

		// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

