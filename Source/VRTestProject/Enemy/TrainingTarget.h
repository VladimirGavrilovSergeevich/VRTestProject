
#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "TrainingTarget.generated.h"


UCLASS()
class VRTESTPROJECT_API ATrainingTarget : public AEnemy
{
	GENERATED_BODY()

public:
	ATrainingTarget();

	UFUNCTION()
	FName GetParameterOnMaterial();

	UFUNCTION()
	float GetParameterValue();

	UFUNCTION()
	void ColorChangeToCalm();

	//AddComponents
	UPROPERTY(EditDefaultsOnly, Category = "Root")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
	UStaticMeshComponent* StaticMesh5;

protected:

	UFUNCTION()
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

private:

    UPROPERTY()
	FName ParameterOnMaterial = "ParamEmissive";

	UPROPERTY()
	float ParameterValue = 0;

	UPROPERTY()
	FTimerHandle FTimerHandleColorChangeToCalm;
};
