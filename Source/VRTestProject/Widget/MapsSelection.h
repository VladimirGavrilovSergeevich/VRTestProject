// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VRCharacter.h"
#include "Components/Button.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapsSelection.generated.h"

UCLASS()
class VRTESTPROJECT_API UMapsSelection : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LevelChangeButton;

    virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
	void LevelChange();
};
