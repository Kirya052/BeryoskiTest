// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlayerController.h"
#include "Pawn\PlayerPawn.h"

void APawnPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedPawn = Cast<APlayerPawn>(InPawn);
}

void APawnPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("RotateRight", this, &APawnPlayerController::RotateRight);
	InputComponent->BindAction("ChangeForce", EInputEvent::IE_Pressed, this, &APawnPlayerController::ChangeForce);
	InputComponent->BindAction("Move", EInputEvent::IE_Released, this, &APawnPlayerController::Move);
	InputComponent->BindAction("SpecialAbility", EInputEvent::IE_Pressed, this, &APawnPlayerController::SpecialAbility);
}

void APawnPlayerController::Move()
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->CancelMovementAbility();
	}
}

void APawnPlayerController::ChangeForce()
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->ActivateMovementAbility();
	}
}

void APawnPlayerController::RotateRight(float Value)
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->RotateRight(Value);
	}
}

void APawnPlayerController::SpecialAbility()
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->SpecialAbility();
	}
}
