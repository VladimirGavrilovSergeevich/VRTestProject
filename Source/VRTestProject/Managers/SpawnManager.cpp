
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
	CurrentGameInstance = Cast<UVRTestProjectGameInstance>(GetWorld()->GetGameInstance());
	check(CurrentGameInstance);
	if (IsValid(GetWorld()->GetFirstPlayerController()))
	{
		CurrentPawn = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
	//check(CurrentPawn);
	check(GetWorld());
}
void ASpawnManager::SpawnWeaponFromUI(LastWeaponInHand NameWeapon)
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

	return SpawnWeaponActor;
}

void ASpawnManager::ChoiceLastWeaponInHand()
{
	if (IsValid(CurrentPawn->GetAttachedActorLeftHand()))
	{
		ChoiceNowForLeftOrRightHand(CurrentPawn->GetAttachedActorLeftHand(), CurrentGameInstance->LastWeaponInLeftHand);
	}
	else
	{
		CurrentGameInstance->LastWeaponInLeftHand = LastWeaponInHand::None;
	}

	if (IsValid(CurrentPawn->GetAttachedActorRightHand()))
	{
		ChoiceNowForLeftOrRightHand(CurrentPawn->GetAttachedActorRightHand(), CurrentGameInstance->LastWeaponInRightHand);
	}	
	else
	{
		CurrentGameInstance->LastWeaponInRightHand = LastWeaponInHand::None;
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

