
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class VRTESTPROJECT_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemy();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
