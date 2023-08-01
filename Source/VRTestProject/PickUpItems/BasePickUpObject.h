
#pragma once

#include "Interfaces/InteractionWithObjects.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUpObject.generated.h"

UCLASS()
class VRTESTPROJECT_API ABasePickUpObject : public AActor, public IInteractionWithObjects
{
	GENERATED_BODY()
	
public:	

	ABasePickUpObject();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	//Interfaces
	UFUNCTION()
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	UFUNCTION()
	virtual void Drop() override;

	UFUNCTION()
	virtual void Fire() override;

	UFUNCTION()
	virtual void StopFire() override;

	UFUNCTION()
	virtual void LeftHandAmmoInWeapon(int32 AmmoCount) override;

	UFUNCTION()
	virtual void RightHandAmmoInWeapon(int32 AmmoCount) override;
};
