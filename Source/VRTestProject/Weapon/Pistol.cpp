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

	TArray<USceneComponent*> a;
	AttachTo->GetChildrenComponents(true,a);
	a.FindItemByClass(UHealthBar);
		
}

void APistol::Drop()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetSimulatePhysics(true);
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

		auto HealthBarRef = Cast<UHealthBar>(UGameplayStatics::GetActorOfClass(GetWorld(), UHealthBar::StaticClass()));
		//auto HealthBarRef = Cast<UHealthBar>(UHealthBar::StaticClass);
		HealthBarRef->AmmoCountForUI = CurrentAmmoCount;
	}
}

void APistol::StopFire()
{
}

bool APistol::AmmoCheck()
{
	if(CurrentAmmoCount-- <= 0)
	{
		return false;
	}
	else
	{
		CurrentAmmoCount = 0;
		return true;
	}
}

void APistol::LoadAmmoIntoWeapon()
{
	CurrentAmmoCount = MaxAmmoCount;
}

void APistol::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetClass() == USkeletalMeshComponent::StaticClass() && LastOverlapActorComp != OtherComp)
	{
		LastOverlapActorComp = OtherComp;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Overlap: %s"), *OtherComp->GetName()));
		LoadAmmoIntoWeapon();
	}

}

