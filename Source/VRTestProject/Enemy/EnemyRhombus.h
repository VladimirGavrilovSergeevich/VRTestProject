// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
};
