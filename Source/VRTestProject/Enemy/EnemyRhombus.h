// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyBullet.h"
#include "VRCharacter.h"
#include "CoreMinimal.h"
#include "Enemy/TrainingTarget.h"
#include "EnemyRhombus.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API AEnemyRhombus : public ATrainingTarget
{
	GENERATED_BODY()

public:
	AEnemyRhombus();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh9;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* SceneComponent1;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* SceneComponent2;

	UPROPERTY()
	FTimerHandle FTimerHandleColorChangeToCalmMuzzle;

	UPROPERTY()
	FTimerHandle FTimerHandleFire;

	UPROPERTY()
	FTimerHandle FTimerHandleStopFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyBullet> BP_EnemyBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVRCharacter* CharacterRef = nullptr;

	UPROPERTY()
	bool FireOn = false;

	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
	void ColorChangeToCalmMuzzle();

	virtual void Fire();

	UFUNCTION()
	void StopFire();

	virtual void Tick(float DeltaTime) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
