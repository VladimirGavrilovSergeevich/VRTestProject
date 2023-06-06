
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
	check(GetWorld());
}

AActor* ASpawnManager::SpawnWeapon(TEnumAsByte<LastWeaponInHand> &Weapon, FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnWeaponActor;

		switch (Weapon.GetValue())
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

		ClearValueOfWeaponInHand(Weapon);

	return SpawnWeaponActor;
}

void ASpawnManager::ChoiceLastWeaponInHand()
{
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
	if (!Hand)
	{
		return;
	}

	if (Hand->GetClass()->IsChildOf(APistol::StaticClass()))
	{
		LastWeaponInHand = LastWeaponInHand::Pistol;
	}
	else if (Hand->GetClass()->IsChildOf(AUzi::StaticClass()))
	{
		LastWeaponInHand = LastWeaponInHand::Uzi;
	}
	else
	{
		LastWeaponInHand = LastWeaponInHand::None;
	}
	
}

void ASpawnManager::ClearValueOfWeaponInHand(TEnumAsByte<LastWeaponInHand>& Weapon)
{
	Weapon = LastWeaponInHand::None;
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

