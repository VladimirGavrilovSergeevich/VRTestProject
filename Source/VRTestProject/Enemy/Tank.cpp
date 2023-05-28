// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Tank.h"
#include "Kismet/KismetMathLibrary.h"

ATank::ATank():Super()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Root->SetupAttachment(RootComponent);
	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh1");
	StaticMesh1->SetupAttachment(Root);
	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh2");
	StaticMesh2->SetupAttachment(Root);
	StaticMesh3 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh3");
	StaticMesh3->SetupAttachment(StaticMesh2);
	SceneComponent1 = CreateDefaultSubobject<USceneComponent>("MuzzleShootingPoint1");
	SceneComponent1->SetupAttachment(StaticMesh2);
	StartTankLocation = GetActorLocation();
	EndTankLocation = StartTankLocation + GetActorForwardVector() * 300;
	//OnActorHit.AddDynamic(this, &AEnemyRhombus::OnHit);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(((cos(GetGameTimeSinceCreation()/10) * 100 * DeltaTime)),0,0));
	//UKismetMathLibrary::VInterpTo(StartTankLocation, EndTankLocation, DeltaTime, 15);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

}

//void ATank::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
//{
	//Super::OnHit(SelfActor, OtherActor, NormalImpulse, Hit);
	//if (!OtherActor->GetClass()->IsChildOf(ACharacterBullet::StaticClass()) || FireOn)
	//{
	//	return;
	//}
	//FireOn = true;
//}
