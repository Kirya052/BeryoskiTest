// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BERYOSKIGAME_API APawnPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;

private:
	void Move();
	void ChangeForce();

	void RotateRight(float Value);

	void SpecialAbility();

	TSoftObjectPtr<class APlayerPawn> CachedPawn;
};
