
#include "PickUpItems/PickUpCube.h"

APickUpCube::APickUpCube()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

void APickUpCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUpCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpCube::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), CurrentObjectSocketName);
	UE_LOG(LogTemp, Warning, TEXT("PickUpCube"));
}

void APickUpCube::Drop()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetSimulatePhysics(true);
}

