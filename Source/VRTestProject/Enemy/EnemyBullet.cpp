

#include "Enemy/EnemyBullet.h"
#include "TimerManager.h"

AEnemyBullet::AEnemyBullet()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	bReplicates = true;
	SetReplicateMovement(true);
}

void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FTimerHandleDestroy, this, &AEnemyBullet::BulletDestroy, 5, false);	
}

void AEnemyBullet::BulletDestroy()
{
	Destroy();
}

void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

