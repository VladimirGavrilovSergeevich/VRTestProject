// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_TestProjectGameMode.h"

void AVR_TestProjectGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	
	MatchHasStarted.Broadcast();//TODO
}
