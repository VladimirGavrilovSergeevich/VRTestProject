// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Uzi.h"

AUzi::AUzi()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AUzi::OnOverlapBegin);
}

void AUzi::Tick(float DeltaTime)
{
	if (BurstFire)
	{
		Fire();
	}
}

void AUzi::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);

	CharacterRef = AttachTo->GetOwner();
	UziAttachToHandNow = AttachTo;
}

void AUzi::Drop()
{
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	StaticMesh->SetSimulatePhysics(true);

	SendCountHandAmmoInWeapon();
	UziAttachToHandNow = nullptr;
}

void AUzi::Fire()
{
	if (AmmoCheck())
	{
		FVector LocationStartBullet = GunMuzzle->GetComponentLocation();
		FRotator RotationStartBullet = GunMuzzle->GetComponentRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ACharacterBullet>(BP_CharacterBullet, LocationStartBullet, RotationStartBullet, SpawnInfo);
		BurstFire = true;

		SendCountHandAmmoInWeapon();
	}
}

void AUzi::StopFire()
{
	BurstFire = false;
}

bool AUzi::AmmoCheck()
{
	--CurrentAmmoCount;
	if (CurrentAmmoCount >= 0)
	{
		return true;
	}
	else
	{
		CurrentAmmoCount = 0;
		return false;
	}
}

void AUzi::SendCountHandAmmoInWeapon()
{
	IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(CharacterRef);
	if (Interface && UziAttachToHandNow != nullptr)
	{
		if (UziAttachToHandNow->GetName() == TEXT("HandMeshLeft"))
		{
			Interface->LeftHandAmmoInWeapon(CurrentAmmoCount);
		}
		else
		{
			Interface->RightHandAmmoInWeapon(CurrentAmmoCount);
		}

	}
}

void AUzi::LoadAmmoIntoWeapon()
{
	CurrentAmmoCount = MaxAmmoCount;
}

void AUzi::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetClass() == USkeletalMeshComponent::StaticClass() && UziAttachToHandNow != OtherComp) // reload with other hand
	{
		LoadAmmoIntoWeapon();

		SendCountHandAmmoInWeapon();
	}

}
