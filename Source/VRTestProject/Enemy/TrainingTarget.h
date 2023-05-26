// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "TrainingTarget.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API ATrainingTarget : public AEnemy
{
	GENERATED_BODY()

public:
	ATrainingTarget();
	
	UPROPERTY(EditDefaultsOnly, Category = "Root")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh5;



	UPROPERTY()
	FName ParameterOnMaterial{ "ParamEmissive" };

	UPROPERTY()
	float ParameterValue{ 0 };

	UPROPERTY()
	FTimerHandle FTimerHandleColorChangeToCalm;


	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void ColorChangeToCalm();

};
