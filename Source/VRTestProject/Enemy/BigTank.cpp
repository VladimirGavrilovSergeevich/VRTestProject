// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BigTank.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/TransformCalculus3D.h"

ABigTank::ABigTank():Super()
{
	//resetup components
	StaticMesh3->SetupAttachment(Root);
	StaticMesh8->SetupAttachment(StaticMesh3);
	StaticMesh2->SetupAttachment(StaticMesh3);
	SceneComponent2->SetupAttachment(StaticMesh3);
}



void ABigTank::Tick(float DeltaTime)
{
	for (int i = 0; i < AllAVRCharacterOnMap.Num(); i++)
	{
		if (GetSquaredDistanceTo(AllAVRCharacterOnMap[i]) < GetSquaredDistanceTo(CharacterRef))
		{
			CharacterRef = AllAVRCharacterOnMap[i];
		}
	}

	if (IsValid(CharacterRef))
	{
		AddActorLocalOffset(FVector(((cos(GetGameTimeSinceCreation() / 10) * 100 * DeltaTime)), 0, 0));// motion actor

		FRotator RotationTankGun(0, UKismetMathLibrary::FindLookAtRotation(StaticMesh3->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw, 0); 
		StaticMesh3->SetWorldRotation(RotationTankGun); // turn to character
	}
}

void ABigTank::Fire()
{
	if (IsValid(CharacterRef))
	{
		FRotator RotationStartRhombus(0, UKismetMathLibrary::FindLookAtRotation(SceneComponent2->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw, 0);// bullet turn to character

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEnemyBullet* CurrentEnemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, SceneComponent2->GetComponentLocation(), RotationStartRhombus, SpawnInfo);//fire
		CurrentEnemyBullet->SetActorScale3D(FVector(1.0f));

	}
}

void ABigTank::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(SelfActor, OtherActor, NormalImpulse, Hit);
}
