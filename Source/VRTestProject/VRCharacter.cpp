
#include "VRCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"



AVRCharacter::AVRCharacter() :
	//init Variable
	CanCharacterRotation(false),
	MinRateForCharacterRotation(0.3f),
	CanTryGrabLeft(true),
	CanTryGrabRight(true)
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
	    if (GetLeftGripValue() > 0.5f)
	    {
		    if (!CanTryGrabLeft)
		    {
	 	  	return;
		    }
		    CanTryGrabLeft = false;
		    if (AttachedActorLeftHand == nullptr)
		    {
			    AttachedActorLeftHand = GetGrabItemNearMotionController(MotionControllerLeft, HandMeshLeft);
			    if (AttachedActorLeftHand != nullptr)
			    {
					//Cast<>(AttachedActorLeftHand)
			   	  CheckAndCallPickUpViaInterface(AttachedActorLeftHand, HandMeshLeft, "None");
				    if (AttachedActorRightHand == AttachedActorLeftHand)
				    {
					
				 	AttachedActorRightHand = nullptr;
				    }
			    }
		    }	
	    }
	    else
	    {
		    if (AttachedActorLeftHand != nullptr)
		    {
				IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorLeftHand);
				if (Interface)
				{
					Interface->Drop();
					AttachedActorLeftHand = nullptr;
				}		
		    }
    	 CanTryGrabLeft = true;
	    }
    }
}

void AVRCharacter::GripRight(float Rate)
{
	if (IsValid(RightHandAnimInstance))
	{
		RightHandAnimInstance->Grip = Rate;
		if (GetRightGripValue() > 0.5f)
		{
			if (!CanTryGrabRight)
			{
				return;
			}
			CanTryGrabRight = false;
			if (AttachedActorRightHand == nullptr)
			{
				AttachedActorRightHand = GetGrabItemNearMotionController(MotionControllerRight, HandMeshRight);
				if (AttachedActorRightHand != nullptr)
				{
					CheckAndCallPickUpViaInterface(AttachedActorRightHand, HandMeshRight, "None");
					if (AttachedActorLeftHand == AttachedActorRightHand)
					{
						AttachedActorLeftHand = nullptr;
					}
				}
			}
		}
		else
		{
			if (AttachedActorRightHand != nullptr)
			{
				IInteractionWithObjects* Interface = Cast<IInteractionWithObjects>(AttachedActorRightHand);
				if (Interface)
				{
					Interface->Drop();
					AttachedActorRightHand = nullptr;
				}	
			}
			CanTryGrabRight = true;
		}
	}
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

float AVRCharacter::GetLeftGripValue()
{
	return LeftHandAnimInstance->Grip;
}

float AVRCharacter::GetRightGripValue()
{
	return RightHandAnimInstance->Grip;
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
				//CheckingAndCallEventInInterface(Interface->EventInInterface())
			}
		}
	}

	return NearestOverlappingActor;
}


