// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HealthBar.h"


float UHealthBar::GetHealth()
{
    const auto OwnerPlayer = Cast<AVRCharacter>(GetOwningPlayerPawn());
    if (OwnerPlayer)
    {
        return OwnerPlayer->GetHealth();
    }
    else
    {
        return 0.0f;
    }
}
