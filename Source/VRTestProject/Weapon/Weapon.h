
#pragma once

#include "CharacterBullet.h"
#include "Components/BoxComponent.h"
#include "PickUpItems/BasePickUpObject.h"
#include "Weapon.generated.h"

UCLASS()
class VRTESTPROJECT_API AWeapon : public ABasePickUpObject
{
	GENERATED_BODY()
	
public:	

	AWeapon();

	virtual void Tick(float DeltaTime) override;

	//Interfaces
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	virtual void Drop() override;


	UFUNCTION()
	bool AmmoCheck();

	UFUNCTION()
	void LoadAmmoIntoWeapon();

	UFUNCTION()
	void SendCountHandAmmoInWeapon(int32 CurrentAmmoCountInWeapon);

	//AddWeaponComponents
	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* GunMuzzle;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	UBoxComponent* CollisionMesh;
	//

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName CurrentObjectSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacterBullet> BP_CharacterBullet;

	UPROPERTY()
	int32 MaxAmmoCount;

	UPROPERTY()
	int32 CurrentAmmoCount;

	UPROPERTY()
	AActor* CharacterRef;

	UPROPERTY()
	USceneComponent* WeaponAttachToHandNow;

	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
