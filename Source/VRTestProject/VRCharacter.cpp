
#include "VRCharacter.h"
#include "Kismet/KismetMathLibrary.h"


AVRCharacter::AVRCharacter() :
	//init Variable
	CanCharacterRotation(false),
	MinRateForCharacterRotation(0.3f)
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
	LeftHandAnimInstance->Grip = Rate;
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

