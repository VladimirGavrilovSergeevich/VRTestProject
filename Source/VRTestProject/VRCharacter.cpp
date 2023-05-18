

#include "VRCharacter.h"

AVRCharacter::AVRCharacter()
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
	
}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

