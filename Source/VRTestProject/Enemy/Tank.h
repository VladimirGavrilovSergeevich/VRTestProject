// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "VRCharacter.h"
#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API ATank : public AEnemy
{
	GENERATED_BODY()
public:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Root")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh3;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* SceneComponent1;

	UPROPERTY()
	FVector StartTankLocation;

	UPROPERTY()
	FVector EndTankLocation;


	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;



	//UFUNCTION()
	//void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
	
