
#pragma once

#include "Interfaces/InteractionWithObjects.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class VRTESTPROJECT_API AWeapon : public AActor, public IInteractionWithObjects
{
	GENERATED_BODY()
	
public:	

	AWeapon();

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

	UFUNCTION()
	virtual void StopFire() override;

};