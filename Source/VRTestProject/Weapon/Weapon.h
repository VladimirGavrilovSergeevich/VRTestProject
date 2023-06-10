
#pragma once

#include "CharacterBullet.h"
#include "Components/BoxComponent.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USceneComponent* GunMuzzle;

	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	UBoxComponent* CollisionMesh;

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

public:	

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(Category = "InterfaceForObject")
	virtual void PickUp(USceneComponent* AttachTo, FName SocketName) override;

	UFUNCTION(Category = "InterfaceForObject")
	virtual void Drop() override;

	UFUNCTION(Category = "InterfaceForObject")
	virtual void Fire() override;

	UFUNCTION(Category = "InterfaceForObject")
	virtual void StopFire() override;

	UFUNCTION(Category = "InterfaceForObject")
	virtual void LeftHandAmmoInWeapon(int32 AmmoCount) override;

	UFUNCTION(Category = "InterfaceForObject")
	virtual void RightHandAmmoInWeapon(int32 AmmoCount) override;


	UFUNCTION()
	bool AmmoCheck();

	UFUNCTION()
	void LoadAmmoIntoWeapon();

	UFUNCTION()
	void SendCountHandAmmoInWeapon(int32 CurrentAmmoCountInWeapon);
	
};
