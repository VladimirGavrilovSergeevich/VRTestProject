// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HealthBar.h"


float UHealthBar::GetHealthPercent()
{
    const auto OwnerPlayer = Cast<AVRCharacter>(GetOwningPlayerPawn());
    if (OwnerPlayer)
    {
        return  (OwnerPlayer->GetMaxHealth() / 100 * OwnerPlayer->GetHealth())/100;// MaxHealth/100= Value 1 % and * CurrentHealthValue = Current % Health. And /100 for Widget because we need value between 0...1 
    }
    else
    {
        return 0.0f;
    }
}
