
#include "Weapon/ThorHammer.h"
#include "Kismet/KismetMathLibrary.h"


AThorHammer::AThorHammer()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);
}

void AThorHammer::Tick(float DeltaTime)
{
	if (HammerFly)
	{
		AddActorLocalOffset(FVector(0,GetActorLocation().Z * 50 * DeltaTime,0));
	}
}

void AThorHammer::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);
	AttachToLocal = AttachTo;
}

void AThorHammer::Drop()
{
	HammerFly = false;

	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	StaticMesh->SetSimulatePhysics(true);

}

void AThorHammer::Fire()
{
	HammerFly = true;
}

void AThorHammer::StopFire()
{
	HammerFly = false;
	Drop();
	PickUp(AttachToLocal,CurrentObjectSocketName);
}
