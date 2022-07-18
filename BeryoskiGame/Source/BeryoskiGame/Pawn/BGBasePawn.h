// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemInterface.h"
#include "BGBasePawn.generated.h"

class UBGAbilitySystemComponent;
UCLASS()
class BERYOSKIGAME_API ABGBasePawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABGBasePawn();

	virtual void PossessedBy(AController* NewController);

	/**	IAbilitySystemInterface */
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/**	~IAbilitySystemInterface */

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereCollision;

	// AbilitySystem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBGAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	class UBGPawnAttributeSet* AttributeSet;

	void InitGameplayAbilitySystem(AController* NewController);
	
	// ~ AbilitySystem

private:
	bool bIsAbilitiesInitialized = false;
};
