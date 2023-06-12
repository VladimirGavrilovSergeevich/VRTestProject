
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnWeaponPoint.generated.h"

UCLASS()
class VRTESTPROJECT_API ASpawnWeaponPoint : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnWeaponPoint();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
