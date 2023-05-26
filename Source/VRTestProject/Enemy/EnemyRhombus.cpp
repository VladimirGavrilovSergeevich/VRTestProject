// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyRhombus.h"

AEnemyRhombus::AEnemyRhombus()
{
	//Super::ATrainingTarget();
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh6 = CreateDefaultSubobject<UStaticMeshComponent>("Canon1");
	StaticMesh6->SetupAttachment(Root);
	StaticMesh7 = CreateDefaultSubobject<UStaticMeshComponent>("Canon2");
	StaticMesh7->SetupAttachment(Root);
	StaticMesh8 = CreateDefaultSubobject<UStaticMeshComponent>("MuzzleVisual1");
	StaticMesh8->SetupAttachment(Root);
	StaticMesh9 = CreateDefaultSubobject<UStaticMeshComponent>("MuzzleVisual2");
	StaticMesh9->SetupAttachment(Root);

	SceneComponent1 = CreateDefaultSubobject<USceneComponent>("MuzzleShootingPoint1");
	SceneComponent1->SetupAttachment(Root);
	SceneComponent2 = CreateDefaultSubobject<USceneComponent>("MuzzleShootingPoint2");
	SceneComponent2->SetupAttachment(Root);
}
