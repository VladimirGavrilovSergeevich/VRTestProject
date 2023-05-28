// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyBullet.h"
#include "VRCharacter.h"
#include "CoreMinimal.h"
#include "Enemy/TrainingTarget.h"
#include "EnemyRhombus.generated.h"

UCLASS()
class VRTESTPROJECT_API AEnemyRhombus : public ATrainingTarget
{
	GENERATED_BODY()

public:
	AEnemyRhombus();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh7;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh8;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh9;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* SceneComponent1;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* SceneComponent2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyBullet> BP_EnemyBullet;

	UPROPERTY()
	AVRCharacter* CharacterRef = nullptr;

private:
	UPROPERTY()
	FTimerHandle FTimerHandleColorChangeToCalmMuzzle;

	UPROPERTY()
	FTimerHandle FTimerHandleFire;

	UPROPERTY()
	FTimerHandle FTimerHandleStopFire;

	UPROPERTY()
	bool FireOn = false;

	UFUNCTION()
	void StopFire();

public:

	UFUNCTION()
	virtual void Fire();

	virtual void Tick(float DeltaTime) override;
	
protected:

	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void BeginPlay() override;
};
