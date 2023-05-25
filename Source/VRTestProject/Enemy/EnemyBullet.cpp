

#include "Enemy/EnemyBullet.h"

AEnemyBullet::AEnemyBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

