// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/TrainingTarget.h"

ATrainingTarget::ATrainingTarget() : Super()
{
	PrimaryActorTick.bCanEverTick = false;

	//init components
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Root->SetupAttachment(RootComponent);
	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh1");
	StaticMesh1->SetupAttachment(Root);
    StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh2");
	StaticMesh2->SetupAttachment(Root);
	StaticMesh3 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh3");
	StaticMesh3->SetupAttachment(Root);
	StaticMesh4 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh4");
	StaticMesh4->SetupAttachment(Root);
	StaticMesh5 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh5");
	StaticMesh5->SetupAttachment(Root);

	OnActorHit.AddDynamic(this, &ATrainingTarget::OnHit);
}

void ATrainingTarget::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	++ParameterValue;

	StaticMesh1->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 0); //change color to black
	StaticMesh3->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 0);
	StaticMesh5->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 0);

	StaticMesh2->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), ParameterValue); //change color to red
	StaticMesh4->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), ParameterValue);

	GetWorldTimerManager().SetTimer(FTimerHandleColorChangeToCalm, this, &ATrainingTarget::ColorChangeToCalm, 1, false);
}

void ATrainingTarget::ColorChangeToCalm()
{
	ParameterValue = 0;

	StaticMesh1->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 1); //change color to white
	StaticMesh3->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 1);
	StaticMesh5->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 1);

	StaticMesh2->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 0); //change color to black
	StaticMesh4->SetScalarParameterValueOnMaterials(GetParameterOnMaterial(), 0);

	

}

FName ATrainingTarget::GetParameterOnMaterial()
{
	return ParameterOnMaterial;
}

float ATrainingTarget::GetParameterValue()
{
	return ParameterValue;
}

