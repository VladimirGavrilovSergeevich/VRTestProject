// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpawnWeapons.generated.h"

/**
 * 
 */
UCLASS()
class VRTESTPROJECT_API USpawnWeapons : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* SpawnWeaponPistolButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SpawnWeaponUziButton;

	virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
	void SpawnPistolWeapon();

	UFUNCTION()
	void SpawnUziWeapon();
};
