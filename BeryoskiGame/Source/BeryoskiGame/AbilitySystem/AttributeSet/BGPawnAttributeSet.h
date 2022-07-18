// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BGPawnAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BERYOSKIGAME_API UBGPawnAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeSets")
	FGameplayAttributeData Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeSets")
	FGameplayAttributeData MaxHealth = 100.0f;
};
