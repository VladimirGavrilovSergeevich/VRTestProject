// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionWithObjects.h"

#include "PickUpCube.generated.h"

UCLASS()
class VRTESTPROJECT_API APickUpCube : public AActor, public IInteractionWithObjects
{
	GENERATED_BODY()
	
public:	
	APickUpCube();

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
  UStaticMeshComponent* StaticMesh;

  UPROPERTY()
  FName CurrentObjectSocketName{"None"};

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	UFUNCTION()
	virtual void Drop() override;

	UFUNCTION()
	virtual void Fire() override;
};
