
#include "Weapon/Weapon.h"
#include "Net/UnrealNetwork.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>("Collision Mesh");
	CollisionMesh->SetupAttachment(StaticMesh);

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);

	bReplicates = true;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	Drop();
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);

	CharacterRef = AttachTo->GetOwner();
	WeaponAttachToHandNow = AttachTo;

	SendCountHandAmmoInWeapon(CurrentAmmoCount);

	PickUpOrDropFromWeapon = true;
//	if (HasAuthority())
//	{
//		PickUpOnServer(AttachTo, SocketName);
//	}
}

void AWeapon::Drop()
{
	StopFire();
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	StaticMesh->SetSimulatePhysics(true);

	SendCountHandAmmoInWeapon(0);

	WeaponAttachToHandNow = nullptr;
	
}

bool AWeapon::AmmoCheck()
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

void AWeapon::LoadAmmoIntoWeapon()
{
	CurrentAmmoCount = MaxAmmoCount;
}

void AWeapon::SendCountHandAmmoInWeapon(int32 CurrentAmmoCountInWeapon)
{
	IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(CharacterRef);
	if (Interface && WeaponAttachToHandNow != nullptr)
	{
		if (WeaponAttachToHandNow->GetName() == TEXT("HandMeshLeft"))
		{
			Interface->LeftHandAmmoInWeapon(CurrentAmmoCountInWeapon);
		}
		else
		{
			Interface->RightHandAmmoInWeapon(CurrentAmmoCountInWeapon);
		}
	}
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetClass() == USkeletalMeshComponent::StaticClass() && WeaponAttachToHandNow != OtherComp) // reload with other hand
	{
		LoadAmmoIntoWeapon();

		SendCountHandAmmoInWeapon(CurrentAmmoCount);
	}

}

void AWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME_CONDITION(AVRCharacter, VRCharacterHMDStruct, COND_SkipOwner);
	DOREPLIFETIME(AWeapon, StaticMesh);
}

void AWeapon::PickUpOnServer_Implementation(USceneComponent* AttachTo, FName SocketName)
{
	//WeaponAttachToHandNow = AttachTo;
//	PickUpOrDrop = true;
}

void AWeapon::OnRep_PickUpOrDropFromWeapon()
{
	
//	Drop();
//	StaticMesh->SetSimulatePhysics(false);
//	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CurrentObjectSocketName);

//	CharacterRef = AttachTo->GetOwner();
//	WeaponAttachToHandNow = AttachTo;

//	SendCountHandAmmoInWeapon(CurrentAmmoCount);
	PickUp(WeaponAttachToHandNow, "SocketName");
}
