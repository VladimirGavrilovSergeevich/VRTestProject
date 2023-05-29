
#pragma once

#include "CharacterBullet.h"
#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Uzi.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API AUzi : public AWeapon
{
	GENERATED_BODY()

public:
	AUzi();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* GunMuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
	FName CurrentObjectSocketName = "UziSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacterBullet> BP_CharacterBullet;
private:

	UPROPERTY()
	bool BurstFire = false;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	virtual void Drop() override;

	virtual void Fire() override;

	virtual void StopFire() override;
};


