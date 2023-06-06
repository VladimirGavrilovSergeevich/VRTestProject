
#include "Managers/SpawnManager.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

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

	AActor* SpawnWeaponActor;
		switch (Weapon)

		{
		case::LastWeaponInHand::None:
			SpawnWeaponActor = nullptr;
			break;

	    case::LastWeaponInHand::Pistol:
			SpawnWeaponActor = GetWorld()->SpawnActor<APistol>(BP_Pistol, Location, Rotation, SpawnInfo);
	        break;

		case::LastWeaponInHand::Uzi:
			SpawnWeaponActor = GetWorld()->SpawnActor<AUzi>(BP_Uzi, Location, Rotation, SpawnInfo);
			break;

		default:
			SpawnWeaponActor = nullptr;
			break;
		}
		ClearValueOfWeaponInHand();
	return SpawnWeaponActor;
}

void ASpawnManager::ChoiceLastWeaponInHand()
{
	check(GetWorld());
	CurrentPawn = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!CurrentPawn)
	{
		return;
	}	
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

void ASpawnManager::ClearValueOfWeaponInHand()
{
	CurrentGameInstance->LastWeaponInLeftHand = LastWeaponInHand::None;
	CurrentGameInstance->LastWeaponInRightHand = LastWeaponInHand::None;
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

