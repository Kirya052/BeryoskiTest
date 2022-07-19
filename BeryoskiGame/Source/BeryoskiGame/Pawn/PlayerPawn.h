// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/BGBasePawn.h"
#include "GameplayTagContainer.h"
#include "PlayerPawn.generated.h"

UCLASS()
class BERYOSKIGAME_API APlayerPawn : public ABGBasePawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	void ActivateMovementAbility();
	void CancelMovementAbility();

	void RotateRight(float Value);
	
	bool CanMove();

	void SpecialAbility();

	FTimerHandle AbilityTimer;

	FVector GetEyesPosition();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components | Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components | Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float Radius = 100.0f;

	//AbilitySystem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	FGameplayTag MovementAbilityTag;

	// ~ AbilitySystem
private:
	void StartLightning();

	FRotator RotateValue;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
};
