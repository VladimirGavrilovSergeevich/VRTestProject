
#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBullet.generated.h"

UCLASS()
class VRTESTPROJECT_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementComponent")
		UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};