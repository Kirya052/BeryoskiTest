// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class BERYOSKIGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	void ChangeForce();
	void AddForceMultiply();
	void Move();

	void RotateRight(float Value);

	FTimerHandle ForceTimer;

	void SpecialAbility();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components | Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components | Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	float Force = 10000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	int ForceMultiply = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	int MaxForceMultiply = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	float ChangeForceSpeed = 0.5f;

private:
	bool CanMove();
};
