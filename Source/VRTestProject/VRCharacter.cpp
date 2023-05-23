
#include "Engine/World.h"
#include "VRCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"


AVRCharacter::AVRCharacter() :
	//init Variable
	CanCharacterRotation(false),
	MinRateForCharacterRotation(0.3f),
	CanTryGrab(true)
{
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>("VRCamera");
	VRCamera->SetupAttachment(RootComponent);

	Center = CreateDefaultSubobject<USceneComponent>("Center");
	Center->SetupAttachment(RootComponent);

	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerRight");
	MotionControllerRight->SetupAttachment(Center);

	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerLeft");
	MotionControllerLeft->SetupAttachment(Center);

	HandMeshRight = CreateDefaultSubobject<USkeletalMeshComponent>("HandMeshRight");
	HandMeshRight->SetupAttachment(MotionControllerRight);

	HandMeshLeft = CreateDefaultSubobject<USkeletalMeshComponent>("HandMeshLeft");
	HandMeshLeft->SetupAttachment(MotionControllerLeft);

	
	LeftHandAnimInstance = Cast<UHandAnimInstance>(HandMeshLeft->GetAnimInstance());
	RightHandAnimInstance = Cast<UHandAnimInstance>(HandMeshRight->GetAnimInstance());

}

void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
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
	if(IsValid(LeftHandAnimInstance))
	{

	
	LeftHandAnimInstance->Grip = Rate;
	if (LeftHandAnimInstance->Grip > 0.5f)
	{
		if (!IsValid(AttachedActorLeftHand))
		{
			AttachedActorLeftHand = GetGrabItemNearMotionController(MotionControllerLeft, HandMeshLeft);
			CheckInterface(AttachedActorLeftHand, HandMeshLeft, "None");
		}
		
	}
	else
	{
		if (IsValid(AttachedActorLeftHand))
		{
			if (AttachedActorLeftHand->GetRootComponent()->GetAttachParent() == HandMeshLeft)
			{
				IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorLeftHand);
				if (Interface)
				{
					Interface->Drop();
					AttachedActorLeftHand = nullptr;
				}
			}
		}
	}
    }
	else
	{
		LeftHandAnimInstance = Cast<UHandAnimInstance>(HandMeshLeft->GetAnimInstance());
	}
}

void AVRCharacter::GripRight(float Rate)
{
	RightHandAnimInstance->Grip = Rate;
}

void AVRCharacter::TriggerLeft(float Rate)
{
	LeftHandAnimInstance->Trigger = Rate;
}

void AVRCharacter::TriggerRight(float Rate)
{
	RightHandAnimInstance->Trigger = Rate;
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
	else if(Rate < (-1)*MinRateForCharacterRotation && CanCharacterRotation)
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

void AVRCharacter::CheckInterface(AActor* TestActor, USceneComponent* AttachTo, FName SocketName)
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
		LocalGrabPosition = MotionControllerLeft->GetRightVector() * 5.0f + MotionController->GetComponentLocation();
	}
	else
	{
		LocalGrabPosition = MotionControllerRight->GetRightVector() * (-5.0f) + MotionController->GetComponentLocation();
	}
	TArray<FHitResult> OutActors;
	FCollisionShape MySphere = FCollisionShape::MakeSphere(5.0f);
	FCollisionQueryParams Params("GrabSphere", false, this);
	if (GetWorld()->SweepMultiByObjectType(OutActors, LocalGrabPosition, LocalGrabPosition, FQuat::Identity, ECC_WorldDynamic, MySphere, Params))
	{
		float LocalNearestActorDistance = 1000000;
		for (FHitResult CurrentActorResult : OutActors)
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

