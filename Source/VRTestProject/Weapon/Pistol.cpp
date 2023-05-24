// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Pistol.h"

APistol::APistol()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	GunMuzzle = CreateDefaultSubobject<USceneComponent>("GunMuzzle");
	GunMuzzle->SetupAttachment(StaticMesh);
}
