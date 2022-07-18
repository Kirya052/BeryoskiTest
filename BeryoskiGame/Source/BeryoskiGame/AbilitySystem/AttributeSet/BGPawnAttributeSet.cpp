// Fill out your copyright notice in the Description page of Project Settings.


#include "BGPawnAttributeSet.h"

void UBGPawnAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute.AttributeName == FString("Health"))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxHealth.GetCurrentValue());
	}
}

void UBGPawnAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute.AttributeName == FString("Health"))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxHealth.GetBaseValue());
	}
}
