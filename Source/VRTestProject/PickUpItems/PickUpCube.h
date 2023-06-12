// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUpItems/BasePickUpObject.h"
#include "PickUpCube.generated.h"

UCLASS()
class VRTESTPROJECT_API APickUpCube : public ABasePickUpObject
{
	GENERATED_BODY()
	
public:	
	APickUpCube();

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
  UStaticMeshComponent* StaticMesh;

  UPROPERTY()
  FName CurrentObjectSocketName{"None"};

public:	
	//Interfaces
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	virtual void Drop() override;
};
