// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Pistol.h"
#include "Widget/HealthBar.h"
#include "Kismet/GameplayStatics.h"

APistol::APistol()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &APistol::OnOverlapBegin);
}

void APistol::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);

	CharacterRef = AttachTo->GetOwner();
	PistolAttachToHandNow = AttachTo;

	SendCountHandAmmoInWeapon();
}

void APistol::Drop()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetSimulatePhysics(true);

	SendCountHandAmmoInWeapon();

	PistolAttachToHandNow = nullptr;



}

void APistol::Fire()
{
	if (AmmoCheck())
	{
		FVector LocationStartBullet = GunMuzzle->GetComponentLocation();
		FRotator RotationStartBullet = GunMuzzle->GetComponentRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ACharacterBullet>(BP_CharacterBullet, LocationStartBullet, RotationStartBullet, SpawnInfo);

		SendCountHandAmmoInWeapon();
	}
}

void APistol::StopFire()
{
}

void APistol::LeftHandAmmoInWeapon(int32 AmmoCount)
{
}

void APistol::RightHandAmmoInWeapon(int32 AmmoCount)
{
}

bool APistol::AmmoCheck()
{
	--CurrentAmmoCount;
	if(CurrentAmmoCount >= 0)
	{
		return true;
	}
	else
	{
		CurrentAmmoCount = 0;
		return false;
	}
}

void APistol::LoadAmmoIntoWeapon()
{
	CurrentAmmoCount = MaxAmmoCount;
}

void APistol::SendCountHandAmmoInWeapon()
{
	IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(CharacterRef);
	if (Interface && PistolAttachToHandNow != nullptr)
	{
		if (PistolAttachToHandNow->GetName() == TEXT("HandMeshLeft"))
		{
			Interface->LeftHandAmmoInWeapon(CurrentAmmoCount);
		}
		else
		{
			Interface->RightHandAmmoInWeapon(CurrentAmmoCount);
		}

	}

}

void APistol::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetClass() == USkeletalMeshComponent::StaticClass() && PistolAttachToHandNow != OtherComp) // reload with other hand
	{
		LoadAmmoIntoWeapon();

		SendCountHandAmmoInWeapon();
	}

}

