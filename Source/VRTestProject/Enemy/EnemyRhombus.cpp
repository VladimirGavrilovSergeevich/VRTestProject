

#include "Enemy/EnemyRhombus.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterBullet.h"


AEnemyRhombus::AEnemyRhombus()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
//	PrimaryActorTick.bCanEverTick = true;
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
	OnActorHit.AddDynamic(this, &AEnemyRhombus::OnHit);

	//CharacterRef = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AEnemyRhombus::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//Super::OnHit();
	if (!OtherActor->GetClass()->IsChildOf(ACharacterBullet::StaticClass()))
	{
		return;
	}
	StaticMesh8->SetScalarParameterValueOnMaterials(ParameterOnMaterial, ParameterValue);
	StaticMesh9->SetScalarParameterValueOnMaterials(ParameterOnMaterial, ParameterValue);

	GetWorldTimerManager().SetTimer(FTimerHandleColorChangeToCalmMuzzle, this, &AEnemyRhombus::ColorChangeToCalmMuzzle, 1, false);
	GetWorldTimerManager().SetTimer(FTimerHandleFire, this, &AEnemyRhombus::Fire, 1, true);

//	CharacterRef = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
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
	FVector LocationStartBullet = SceneComponent1->GetComponentLocation();
	FRotator RotationStartRhombus(0,0, UKismetMathLibrary::FindLookAtRotation(SceneComponent1->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, LocationStartBullet, RotationStartRhombus, SpawnInfo);

	LocationStartBullet = SceneComponent2->GetComponentLocation();
	RotationStartRhombus = FRotator(0, 0, UKismetMathLibrary::FindLookAtRotation(SceneComponent2->GetComponentLocation(), CharacterRef->GetActorLocation()).Yaw);
	SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, LocationStartBullet, RotationStartRhombus, SpawnInfo);
	}
}

void AEnemyRhombus::Tick(float DeltaTime)
{
//	Super::Tick(DeltaTime);
	 if (PrimaryActorTick.IsTickFunctionRegistered()) {
			UKismetSystemLibrary::PrintString(this, "valid");
		}
}

/*void AEnemyRhombus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FVector::ZeroVector);
	if(IsValid(CharacterRef))
	{
		FVector LocationStartBullet = SceneComponent1->GetComponentLocation();
		FRotator RotationStartRhombus(0, 0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CharacterRef->GetActorLocation()).Yaw);
		//FActorSpawnParameters SpawnInfo;
		//SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SetActorRotation(RotationStartRhombus);
		//GetWorld()->SpawnActor<AEnemyBullet>(BP_EnemyBullet, LocationStartBullet, RotationStartRhombus, SpawnInfo);
	}
}*/

void AEnemyRhombus::BeginPlay()
{
	PrimaryActorTick.RegisterTickFunction(GetWorld()->GetLevel(0));
	CharacterRef = Cast<AVRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//if (PrimaryActorTick.IsTickFunctionRegistered()) {
	//	UKismetSystemLibrary::PrintString(this, "valid");
	//}
}
