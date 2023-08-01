
#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Uzi.generated.h"


UCLASS()
class VRTESTPROJECT_API AUzi : public AWeapon
{
	GENERATED_BODY()

public:

	AUzi();

	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;

	virtual void StopFire() override;

private:

	bool BurstFire = false;
};


