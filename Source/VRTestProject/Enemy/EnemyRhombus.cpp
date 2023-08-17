

#include "Enemy/EnemyRhombus.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterBullet.h"


AEnemyRhombus::AEnemyRhombus():Super()
{
	//init components
	PrimaryActorTick.bCanEverTick = true;
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
}

void AEnemyRhombus::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(SelfActor, OtherActor, NormalImpulse, Hit);
	if (!OtherActor->GetClass()->IsChildOf(ACharacterBullet::StaticClass()) || FireOn)
	{
		return;
	}
	GetAllCharacters();
	FireOn = true;
	StaticMesh8->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 1); //change color to red
	StaticMesh9->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 1);

	GetWorldTimerManager().SetTimer(FTimerHandleFire, this, &AEnemyRhombus::Fire, 1, true);
	GetWorldTimerManager().SetTimer(FTimerHandleStopFire, this, &AEnemyRhombus::StopFire, 5, false);

}


void AEnemyRhombus::Fire()
{
	if (IsValid(CharacterRef))
	{	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//shot 1st gun
	FRotator RotationStartBullet(0, UKismetMathLibrary::FindLookAtRotation(SceneComponent1->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw, 0);
	GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, SceneComponent1->GetComponentLocation(), RotationStartBullet, SpawnInfo);
	//shot 2st gun
	RotationStartBullet = FRotator(0,UKismetMathLibrary::FindLookAtRotation(SceneComponent2->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw,0);
	GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, SceneComponent2->GetComponentLocation(), RotationStartBullet, SpawnInfo);
	}
}

void AEnemyRhombus::StopFire()
{
	GetWorldTimerManager().ClearTimer(FTimerHandleFire);
	GetWorldTimerManager().ClearTimer(FTimerHandleStopFire);

	FireOn = false;

	StaticMesh8->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 0); //change color to black
	StaticMesh9->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 0);
}

void AEnemyRhombus::GetAllCharacters()
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVRCharacter::StaticClass(), FoundActors);
	for (int i = 0; i < FoundActors.Num(); ++i)
	{
		if (IsValid(FoundActors[i]))
		{
			AllAVRCharacterOnMap.AddUnique(Cast<AVRCharacter>(FoundActors[i]));
			CharacterRef = AllAVRCharacterOnMap[i];
		}
	}
}

void AEnemyRhombus::Tick(float DeltaTime)
{
	for (int i = 0; i < AllAVRCharacterOnMap.Num(); i++)
	{
		if (GetSquaredDistanceTo(AllAVRCharacterOnMap[i])< GetSquaredDistanceTo(CharacterRef))
		{
			CharacterRef = AllAVRCharacterOnMap[i];
		}
	}
	if (IsValid(CharacterRef))
	{
		AddActorLocalOffset(FVector(0, 0, (cos(GetGameTimeSinceCreation()) * 50 * DeltaTime))); //up and down motion actor

		//TurnToPlayer
		FRotator RotationStartRhombus(0,UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CharacterRef->GetActorLocation()).Yaw,0);
		SetActorRotation(RotationStartRhombus); // Turn to character
	}
}

void AEnemyRhombus::BeginPlay()
{
	Super::BeginPlay();
}
