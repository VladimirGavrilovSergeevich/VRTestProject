
#include "VRCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy/EnemyBullet.h"

//#include "engine.h"
#include "Net/UnrealNetwork.h"

//#include "Components/SceneComponent.h"

#include "Managers/SpawnManager.h"

AVRCharacter::AVRCharacter() :
	//init Variable
	Health(MaxHealth)
{
	PrimaryActorTick.bCanEverTick = true;

	//init and attach components
	VRCamera = CreateDefaultSubobject<UCameraComponent>("VRCamera");
	VRCamera->SetupAttachment(RootComponent);

	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerRight");
	MotionControllerRight->SetupAttachment(RootComponent);

	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerLeft");
	MotionControllerLeft->SetupAttachment(RootComponent);

	HandMeshRight = CreateDefaultSubobject<USkeletalMeshComponent>("HandMeshRight");
	HandMeshRight->SetupAttachment(MotionControllerRight);

	HandMeshLeft = CreateDefaultSubobject<USkeletalMeshComponent>("HandMeshLeft");
	HandMeshLeft->SetupAttachment(MotionControllerLeft);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HPBar");
	WidgetComponent->SetupAttachment(VRCamera);

	WidgetInteractionComponentRight = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteractionRight");
	WidgetInteractionComponentRight->SetupAttachment(MotionControllerRight);

	WidgetInteractionComponentLeft = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteractionLeft");
	WidgetInteractionComponentLeft->SetupAttachment(MotionControllerLeft);

	SplineComponentRight = CreateDefaultSubobject<USplineComponent>("SplineComponentRight");
	SplineComponentRight->SetupAttachment(WidgetInteractionComponentRight);

	SplineComponentLeft = CreateDefaultSubobject<USplineComponent>("SplineComponentLeft");
	SplineComponentLeft->SetupAttachment(WidgetInteractionComponentLeft);

	SplineMeshComponentRight = CreateDefaultSubobject<USplineMeshComponent>("SplineMeshComponentRight");
	SplineMeshComponentRight->SetupAttachment(SplineComponentRight);

	SplineMeshComponentLeft = CreateDefaultSubobject<USplineMeshComponent>("SplineMeshComponentLeft");
	SplineMeshComponentLeft->SetupAttachment(SplineComponentLeft);

	OnActorHit.AddDynamic(this, &AVRCharacter::OnHit);

	bReplicates = true;
}

void AVRCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AVRCharacter, VRCharacterHMDStruct, COND_SkipOwner);
}
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	//init Variable after Cast
	LeftHandAnimInstance = Cast<UHandAnimInstance>(HandMeshLeft->GetAnimInstance());
	RightHandAnimInstance = Cast<UHandAnimInstance>(HandMeshRight->GetAnimInstance());

	CurrentGameInstance = Cast<UVRTestProjectGameInstance>(GetWorld()->GetGameInstance());
	if (!CurrentGameInstance)
	{
		return;
	}
	auto GameManagerRef = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	if (!GameManagerRef)
	{
		return;
	}
	SpawnWeaponInHand(AttachedActorLeftHand, CurrentGameInstance->LastWeaponInLeftHand, HandMeshLeft, GameManagerRef);
	SpawnWeaponInHand(AttachedActorRightHand, CurrentGameInstance->LastWeaponInRightHand, HandMeshRight, GameManagerRef);
	GetWorldTimerManager().SetTimer(FTimerHandleWasTransitionBetweenLevels, this, &AVRCharacter::SetWasTransitionBetweenLevels, 0.5, true); //this is necessary the weapon does not fall from the hands when changing the level

}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SplineConstruction for AllHands
	SplineConstructionToWidget(WidgetInteractionComponentRight, SplineComponentRight, RightHandPointingAtWidget);
	SplineConstructionToWidget(WidgetInteractionComponentLeft, SplineComponentLeft, LeftHandPointingAtWidget);

	UpdateSplineMesh(SplineComponentRight, SplineMeshComponentRight);
	UpdateSplineMesh(SplineComponentLeft, SplineMeshComponentLeft);
	///
	if (!HasAuthority())
	{
		FVRCharacterHMDStruct HMDTempStruct;
		HMDTempStruct.MotionControllerRightLocalLocation = MotionControllerRight->GetRelativeLocation();
		HMDTempStruct.MotionControllerRightLocalRotation = MotionControllerRight->GetRelativeRotation();
		HMDTempStruct.MotionControllerRight = MotionControllerRight;

		HMDTempStruct.MotionControllerLeftLocalLocation = MotionControllerLeft->GetRelativeLocation();
		HMDTempStruct.MotionControllerLeftLocalRotation = MotionControllerLeft->GetRelativeRotation();
		HMDTempStruct.MotionControllerLeft = MotionControllerLeft;

		HMDTempStruct.VRCameraLocalLocation = VRCamera->GetRelativeLocation();
		HMDTempStruct.VRCameraLocalRotation = VRCamera->GetRelativeRotation();
		HMDTempStruct.VRCamera = VRCamera;

		RepVRCharacterHMDStructFromClient(HMDTempStruct);
	}
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Bind HandAnimation == Grab/Fire events
	PlayerInputComponent->BindAxis("GripLeft",this, &AVRCharacter::GripLeft);
	PlayerInputComponent->BindAxis("GripRight", this, &AVRCharacter::GripRight);
	PlayerInputComponent->BindAxis("TriggerLeft", this, &AVRCharacter::TriggerLeft);
	PlayerInputComponent->BindAxis("TriggerRight", this, &AVRCharacter::TriggerRight);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVRCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CharacterRotation", this, &AVRCharacter::CharacterRotation);

	//BindAction for WidgetInteraction
	PlayerInputComponent->BindAction("TriggerRightAction", IE_Pressed, this, &AVRCharacter::TriggerRightActionPressed);
	PlayerInputComponent->BindAction("TriggerLeftAction", IE_Pressed, this, &AVRCharacter::TriggerLeftActionPressed);
	PlayerInputComponent->BindAction("TriggerRightAction", IE_Released,this, &AVRCharacter::TriggerRightActionReleased);
	PlayerInputComponent->BindAction("TriggerLeftAction", IE_Released, this, &AVRCharacter::TriggerLeftActionReleased);
}

void AVRCharacter::GripLeft(float Rate)
{
	if (!IsValid(LeftHandAnimInstance))
	{
		return;
	}

	LeftHandAnimInstance->Grip = Rate;

	if (LeftHandAnimInstance->Grip > 0.5f)
	{
		if (!CanTryGrabLeft)
		{
	 	    return;
		}
		CanTryGrabLeft = false;
		if (AttachedActorLeftHand != nullptr)
		{
		    return;
		}
		AttachedActorLeftHand = GetGrabItemNearMotionController(MotionControllerLeft, HandMeshLeft);
		if (AttachedActorLeftHand == nullptr)
		{
		    return;
		}
		CheckAndCallPickUpViaInterface(AttachedActorLeftHand, HandMeshLeft, "None");
		if (AttachedActorRightHand == AttachedActorLeftHand)
		{
		    AttachedActorRightHand = nullptr;
		}	      
    }
	else
	{
		CanTryGrabLeft = true;

		if (AttachedActorLeftHand == nullptr)
		{
			return;
		}
		if (WeaponDropDelay)
		{
			return;
		}
		IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorLeftHand);
		if (Interface)
		{
			Interface->Drop();
			AttachedActorLeftHand = nullptr;
		}
	}
}

void AVRCharacter::GripRight(float Rate)
{
	if (!IsValid(RightHandAnimInstance))
	{
		return;
	}
    RightHandAnimInstance->Grip = Rate;

	if (RightHandAnimInstance->Grip > 0.5f)
	{
		if (!CanTryGrabRight)
		{
			return;
		}
		CanTryGrabRight = false;
		if (AttachedActorRightHand != nullptr)
		{
			return;
		}
		AttachedActorRightHand = GetGrabItemNearMotionController(MotionControllerRight, HandMeshRight);
		if (AttachedActorRightHand == nullptr)
		{
			return;
		}
		CheckAndCallPickUpViaInterface(AttachedActorRightHand, HandMeshRight, "None");
		if (AttachedActorRightHand == AttachedActorLeftHand)
		{
			AttachedActorLeftHand = nullptr;
		}
	}
	else
	{
		CanTryGrabRight = true;

		if (AttachedActorRightHand == nullptr)
		{
			return;
		}
		if (WeaponDropDelay)
		{
			return;
		}
		IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorRightHand);
		if (Interface)
		{
			Interface->Drop();
			AttachedActorRightHand = nullptr;
		}
	}
}

void AVRCharacter::TriggerLeft(float Rate)
{
	if (!IsValid(LeftHandAnimInstance))
	{
		return;
	}
    LeftHandAnimInstance->Trigger = Rate;
	DoFireAndStopFire(LeftHandAnimInstance->Trigger, CanTryTriggerLeft, AttachedActorLeftHand, CanTryStopFireLeft, LeftHandPointingAtWidget);
}

void AVRCharacter::TriggerRight(float Rate)
{
	if (!IsValid(RightHandAnimInstance))
	{
		return;
	}
	RightHandAnimInstance->Trigger = Rate;
	DoFireAndStopFire(RightHandAnimInstance->Trigger, CanTryTriggerRight, AttachedActorRightHand, CanTryStopFireRight, RightHandPointingAtWidget);
}

void AVRCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(VRCamera->GetForwardVector(), Value);
	}
}

void AVRCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(VRCamera->GetRightVector(), Value);
	}
}

void AVRCharacter::TriggerRightActionPressed()
{
	WidgetInteractionComponentRight->PressPointerKey(EKeys::LeftMouseButton.GetFName());
}

void AVRCharacter::TriggerRightActionReleased()
{
	WidgetInteractionComponentRight->ReleasePointerKey(EKeys::LeftMouseButton.GetFName());
}

void AVRCharacter::TriggerLeftActionPressed()
{
	WidgetInteractionComponentLeft->PressPointerKey(EKeys::LeftMouseButton.GetFName());
}

void AVRCharacter::TriggerLeftActionReleased()
{
	WidgetInteractionComponentLeft->ReleasePointerKey(EKeys::LeftMouseButton.GetFName());
}

void AVRCharacter::CharacterRotation(float Rate)
{
	if (!CanCharacterRotation)
	{
		CanCharacterRotation = UKismetMathLibrary::InRange_FloatFloat(Rate, -0.3f, 0.3f, true, true);
	}

	if (Rate > MinRateForCharacterRotation && CanCharacterRotation)
	{
		AddControllerYawInput(30);
		CanCharacterRotation = false;
	}
	else if(Rate < (-1) * MinRateForCharacterRotation && CanCharacterRotation)
	{
		AddControllerYawInput(-30);
		CanCharacterRotation = false;
	}
}

void AVRCharacter::DoFireAndStopFire(float &TriggerValue, bool &CanTryTrigger, AActor* AttachedActorHand, bool &CanTryStopFire, bool& HandPointingAtWidget)
{
	if (HandPointingAtWidget)
	{
		return;
	}
	if (TriggerValue > 0.5f)
	{
		if (!CanTryTrigger)
		{
			return;
		}
		CanTryTrigger = false;
		if (AttachedActorHand == nullptr)
		{
			return;
		}
		IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorHand);
		if (Interface)
		{
			Interface->Fire();
			CanTryTrigger = false;
			CanTryStopFire = true;
			return;
		}
	}
	else
	{
		CanTryTrigger = true;
		if (!CanTryStopFire || AttachedActorHand == nullptr)
		{
			return;
		}
		IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorHand);
		if (Interface)
		{
			Interface->StopFire();
			CanTryStopFire = false;
		}
	}
}

void AVRCharacter::DoPressButtonOnWidget(float& TriggerValue, bool& CanTryTrigger)
{
	if (TriggerValue > 0.5f)
	{
		if (!CanTryTrigger)
		{
			return;
		}
		WidgetInteractionComponentRight->PressPointerKey(EKeys::LeftMouseButton);
	}
	else
	{
		CanTryTrigger = true;
		WidgetInteractionComponentRight->PressPointerKey(EKeys::LeftMouseButton);
	}

}

void AVRCharacter::ChooseToPressButtonOrShoot()
{
	if (RightHandPointingAtWidget)
	{
	//	
	}
	else
	{
		DoFireAndStopFire(RightHandAnimInstance->Trigger, CanTryTriggerRight, AttachedActorRightHand, CanTryStopFireRight, RightHandPointingAtWidget);
	}
}

void AVRCharacter::SpawnWeaponInHand(AActor* AttachedActorInHand,TEnumAsByte<LastWeaponInHand>& LastWeaponInHand, USkeletalMeshComponent* HandMesh, ASpawnManager* GameManagerRef)
{
	AttachedActorInHand = GameManagerRef->SpawnWeapon(LastWeaponInHand, HandMesh->GetComponentLocation(), HandMesh->GetComponentRotation());

	if (AttachedActorInHand == nullptr)
	{
		return;
	}
	CheckAndCallPickUpViaInterface(AttachedActorInHand, HandMesh, "None");
}

void AVRCharacter::DeadCharacter()
{
	auto GameManagerRef = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	if (!GameManagerRef)
	GameManagerRef->ClearValueOfWeaponInHand(CurrentGameInstance->LastWeaponInLeftHand);
	GameManagerRef->ClearValueOfWeaponInHand(CurrentGameInstance->LastWeaponInRightHand);
	UGameplayStatics::OpenLevel(GetWorld(), "MainMap");
}

void AVRCharacter::PickUp(USceneComponent* AttachTo, FName SocketName)
{
}

void AVRCharacter::Drop()
{
}


void AVRCharacter::CheckAndCallPickUpViaInterface(AActor* AttachedActorInHand, USceneComponent* AttachTo, FName SocketName)
{
	IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorInHand);
	if (Interface)
	{
		Interface->PickUp(AttachTo,SocketName);
	}
}

AActor* AVRCharacter::GetGrabItemNearMotionController(UMotionControllerComponent* MotionController, USkeletalMeshComponent* HandMesh)
{
	AActor* NearestOverlappingActor = nullptr;
	FVector LocalGrabPosition;
	if(MotionController == MotionControllerLeft)
	{
		LocalGrabPosition = MotionControllerLeft->GetRightVector() * 4.0f + MotionController->GetComponentLocation();
	}
	else
	{
		LocalGrabPosition = MotionControllerRight->GetRightVector() * (-4.0f) + MotionController->GetComponentLocation();
	}
	TArray<FHitResult> OutActors;
	FCollisionShape MySphere = FCollisionShape::MakeSphere(4.0f);
	FCollisionQueryParams Params("GrabSphere", false, this);
	if (GetWorld()->SweepMultiByObjectType(OutActors, LocalGrabPosition, LocalGrabPosition, FQuat::Identity, ECC_WorldDynamic, MySphere, Params))// do sphere trace for grab object
	{
		float LocalNearestActorDistance = 1000000;
		for (FHitResult &CurrentActorResult : OutActors)
		{
			IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(CurrentActorResult.GetActor());
			if (Interface)
			{
				float DistanceToCurrentActorResult = (CurrentActorResult.GetActor()->GetActorLocation() - LocalGrabPosition).Size();
				if (DistanceToCurrentActorResult <= LocalNearestActorDistance)
				{
					LocalNearestActorDistance = DistanceToCurrentActorResult;
					NearestOverlappingActor = CurrentActorResult.GetActor();
				}
			}
		}
	}
	return NearestOverlappingActor;
}

void AVRCharacter::Fire()
{
}

void AVRCharacter::StopFire()
{

}
void AVRCharacter::LeftHandAmmoInWeapon(int32 AmmoCount)
{
	LeftHandCurrentAmmoCountInWeapon = AmmoCount;
}
void AVRCharacter::RightHandAmmoInWeapon(int32 AmmoCount)
{
	RightHandCurrentAmmoCountInWeapon = AmmoCount;
}
float AVRCharacter::GetHealth() const
{
	return Health;
}
float AVRCharacter::GetMaxHealth() const
{
	return MaxHealth;
}
int32 AVRCharacter::GetLeftHandCurrentAmmoCountInWeapon()
{
	return LeftHandCurrentAmmoCountInWeapon;
}
int32 AVRCharacter::GetRightHandCurrentAmmoCountInWeapon()
{
	return RightHandCurrentAmmoCountInWeapon;
}
AActor* AVRCharacter::GetAttachedActorLeftHand()
{
	return AttachedActorLeftHand;
}
AActor* AVRCharacter::GetAttachedActorRightHand()
{
	return AttachedActorRightHand;
}
void AVRCharacter::SetWasTransitionBetweenLevels()
{
	WeaponDropDelay = false;
}
void AVRCharacter::UpdateSplineMesh(USplineComponent* SplineComponent, USplineMeshComponent* SplineMeshComponent)
{
	const FVector StartPoint = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	const FVector StartTangent = SplineComponent->GetTangentAtSplinePoint(0, ESplineCoordinateSpace::Local);
	const FVector EndPoint = SplineComponent->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Local);
	const FVector EndTangent = SplineComponent->GetTangentAtSplinePoint(1, ESplineCoordinateSpace::Local);

	SplineMeshComponent->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent);
}
void AVRCharacter::SplineConstructionToWidget(UWidgetInteractionComponent* WidgetInteractionComponent, USplineComponent* SplineComponent, bool& HandPointingAtWidget)
{
	FHitResult HitResult = WidgetInteractionComponent->GetLastHitResult();
	if (HitResult.Location.X != 0)
	{
		SplineComponent->SetLocationAtSplinePoint(1, HitResult.Location, ESplineCoordinateSpace::World);

		HandPointingAtWidget = true;
	}
	else
	{
		const FVector ZeroPointForSplineComponent = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		SplineComponent->SetLocationAtSplinePoint(1, ZeroPointForSplineComponent, ESplineCoordinateSpace::World);

		HandPointingAtWidget = false;
	}

}
void AVRCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!OtherActor->GetClass()->IsChildOf(AEnemyBullet::StaticClass()))
	{
		return;
	}
	Health -= 10;

	if (Health <= 0)
	{
		DeadCharacter();
	}
}

void AVRCharacter::OnRep_VRCharacterHMDStruct()
{
	if (HasAuthority())
	{
		return;
	}
	if (IsValid(MotionControllerRight))
	{
		MotionControllerRight->SetRelativeLocation(VRCharacterHMDStruct.MotionControllerRightLocalLocation);
		MotionControllerRight->SetRelativeRotation(VRCharacterHMDStruct.MotionControllerRightLocalRotation);
	}
	if (IsValid(MotionControllerLeft))
	{
		MotionControllerLeft->SetRelativeLocation(VRCharacterHMDStruct.MotionControllerLeftLocalLocation);
		MotionControllerLeft->SetRelativeRotation(VRCharacterHMDStruct.MotionControllerLeftLocalRotation);
	}
	if (IsValid(VRCamera))
	{
		VRCamera->SetRelativeLocation(VRCharacterHMDStruct.VRCameraLocalLocation);
		VRCamera->SetRelativeRotation(VRCharacterHMDStruct.VRCameraLocalRotation);
	}
}

void AVRCharacter::RepVRCharacterHMDStructFromClient_Implementation(FVRCharacterHMDStruct HMDStruct)
{
	VRCharacterHMDStruct = HMDStruct;
}

bool AVRCharacter::RepVRCharacterHMDStructFromClient_Validate(FVRCharacterHMDStruct HMDStruct)
{
	return true;
}



