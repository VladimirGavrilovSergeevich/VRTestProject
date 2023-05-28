// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyRhombus.h"
#include "BigTank.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API ABigTank : public AEnemyRhombus
{
	GENERATED_BODY()
public:
	ABigTank();

	virtual void Tick(float DeltaTime) override;

	void Fire() override;

	//UFUNCTION()
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) override;
};
