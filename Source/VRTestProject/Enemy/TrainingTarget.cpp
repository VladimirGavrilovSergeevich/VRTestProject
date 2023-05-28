// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/TrainingTarget.h"

ATrainingTarget::ATrainingTarget() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
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
	StaticMesh1->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);
	StaticMesh3->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);
	StaticMesh5->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);

	++ParameterValue;

	StaticMesh2->SetScalarParameterValueOnMaterials(ParameterOnMaterial, ParameterValue);
	StaticMesh4->SetScalarParameterValueOnMaterials(ParameterOnMaterial, ParameterValue);

	GetWorldTimerManager().SetTimer(FTimerHandleColorChangeToCalm, this, &ATrainingTarget::ColorChangeToCalm, 1, false);
}

void ATrainingTarget::ColorChangeToCalm()
{
	StaticMesh2->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);
	StaticMesh4->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 0);

	StaticMesh1->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 1);
	StaticMesh3->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 1);
	StaticMesh5->SetScalarParameterValueOnMaterials(ParameterOnMaterial, 1);

	ParameterValue = 0;

}

void ATrainingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
