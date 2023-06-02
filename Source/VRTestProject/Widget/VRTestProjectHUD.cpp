// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/VRTestProjectHUD.h"

void AVRTestProjectHUD::BeginPlay()
{
	Super::BeginPlay();
	UHealthBar* CurrentHealthBarWidget = CreateWidget<UHealthBar>(GetWorld(), HealthBarWidget);
	if (CurrentHealthBarWidget)
	{
		CurrentHealthBarWidget->AddToViewport(); 
	}
}
