// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpItems/PickUpCube.h"

// Sets default values
APickUpCube::APickUpCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUpCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpCube::PickUp(USceneComponent* AttachTo, FName SocketName)
{
	UE_LOG(LogTemp, Warning, TEXT("PickUpCube"));
}

