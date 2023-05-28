
#include "VRCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy/EnemyBullet.h"



AVRCharacter::AVRCharacter() :
	//init Variable
	CanCharacterRotation(false),
	MinRateForCharacterRotation(0.3f),
	CanTryGrabLeft(true),
	CanTryGrabRight(true),
	CanTryTriggerRight(true),
	CanTryTriggerLeft(true),
	Health(100)
{
	PrimaryActorTick.bCanEverTick = false;

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

	OnActorHit.AddDynamic(this, &AVRCharacter::OnHit);
}

void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	//init Variable after Cast
	LeftHandAnimInstance = Cast<UHandAnimInstance>(HandMeshLeft->GetAnimInstance());
	RightHandAnimInstance = Cast<UHandAnimInstance>(HandMeshRight->GetAnimInstance());
}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	if (LeftHandAnimInstance->Trigger > 0.5f)
	{
		if (!CanTryTriggerLeft)
		{
			return;
		}
		CanTryTriggerLeft = false;
		if (AttachedActorLeftHand == nullptr)
		{
			return;
		}
		IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorLeftHand);
		if (Interface)
		{
			Interface->Fire();
			CanTryTriggerLeft = false;
			return;
		}
	}
	CanTryTriggerLeft = true;
}

void AVRCharacter::TriggerRight(float Rate)
{
	if (!IsValid(RightHandAnimInstance))
	{
		return;
	}
	RightHandAnimInstance->Trigger = Rate;

	if (RightHandAnimInstance->Trigger > 0.5f)
	{
		if (!CanTryTriggerRight)
		{
			return;
		}
		CanTryTriggerRight = false;
		if (AttachedActorRightHand == nullptr)
		{
			return;
		}
		IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorRightHand);
		if (Interface)
		{
			Interface->Fire();
			CanTryTriggerRight = false;
			return;
		}
	}
	CanTryTriggerRight = true;
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

void AVRCharacter::PickUp(USceneComponent* AttachTo, FName SocketName)
{
}

void AVRCharacter::Drop()
{
}


void AVRCharacter::CheckAndCallPickUpViaInterface(AActor* TestActor, USceneComponent* AttachTo, FName SocketName)
{
	IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(TestActor);
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
	FCollisionShape MySphere = FCollisionShape::MakeSphere(5.0f);
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

void AVRCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!OtherActor->GetClass()->IsChildOf(AEnemyBullet::StaticClass()))
	{
		return;
	}
	Health -= 10;

	if (Health <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(),"MainMap");
	}
}



