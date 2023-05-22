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
	// Sets default values for this actor's properties
	APickUpCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;
};
