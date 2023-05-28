

#include "Enemy/EnemyRhombus.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterBullet.h"


AEnemyRhombus::AEnemyRhombus():Super()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	StaticMesh6 = CreateDefaultSubobject<UStaticMeshComponent>("Canon1");
	StaticMesh6->SetupAttachment(Root);
	StaticMesh7 = CreateDefaultSubobject<UStaticMeshComponent>("Canon2");
	StaticMesh7->SetupAttachment(Root);
	StaticMesh8 = CreateDefaultSubobject<UStaticMeshComponent>("MuzzleVisual1");
	StaticMesh8->SetupAttachment(Root);
	StaticMesh9 = CreateDefaultSubobject<UStaticMeshComponent>("MuzzleVisual2");
	StaticMesh9->SetupAttachment(Root);

	SceneComponent1 = CreateDefaultSubobject<USceneComponent>("MuzzleShootingPoint1");
	SceneComponent1->SetupAttachment(Root);
	SceneComponent2 = CreateDefaultSubobject<USceneComponent>("MuzzleShootingPoint2");
	SceneComponent2->SetupAttachment(Root);
	CharacterRef = nullptr;
}

void AEnemyRhombus::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(SelfActor, OtherActor, NormalImpulse, Hit);
	if (!OtherActor->GetClass()->IsChildOf(ACharacterBullet::StaticClass()) || FireOn)
	{
		return;
	}
	FireOn = true;
	StaticMesh8->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 1);
	StaticMesh9->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 1);

	GetWorldTimerManager().SetTimer(FTimerHandleFire, this, &AEnemyRhombus::Fire, 1, true);
	GetWorldTimerManager().SetTimer(FTimerHandleStopFire, this, &AEnemyRhombus::StopFire, 5, false);

}


void AEnemyRhombus::ColorChangeToCalmMuzzle()
{
	StaticMesh8->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);
	StaticMesh9->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);
}

void AEnemyRhombus::Fire()
{
	if (IsValid(CharacterRef))
	{	
	FRotator RotationStartRhombus(0,UKismetMathLibrary::FindLookAtRotation(SceneComponent1->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw,0);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, SceneComponent1->GetComponentLocation(), RotationStartRhombus, SpawnInfo);
	RotationStartRhombus = FRotator(0,UKismetMathLibrary::FindLookAtRotation(SceneComponent2->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw,0);
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, SceneComponent2->GetComponentLocation(), RotationStartRhombus, SpawnInfo);
	}
}

void AEnemyRhombus::StopFire()
{
	GetWorldTimerManager().ClearTimer(FTimerHandleFire);
	GetWorldTimerManager().ClearTimer(FTimerHandleStopFire);
	FireOn = false;
	StaticMesh8->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);
	StaticMesh9->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);
}

void AEnemyRhombus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UKismetSystemLibrary::PrintString(this, "valid");
	if (IsValid(CharacterRef))
	{
		AddActorLocalOffset(FVector(0, 0, (cos(GetGameTimeSinceCreation()) * 50 * DeltaTime)));
		FRotator RotationStartRhombus(0,UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CharacterRef->GetActorLocation()).Yaw,0);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SetActorRotation(RotationStartRhombus);
	}
}


void AEnemyRhombus::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	CharacterRef = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
