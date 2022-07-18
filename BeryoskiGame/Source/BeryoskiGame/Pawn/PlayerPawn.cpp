// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components\SphereComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Components\ArrowComponent.h"
#include "DrawDebugHelpers.h"

APlayerPawn::APlayerPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(SphereCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 1000.0f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(SphereCollision);

}

void APlayerPawn::ChangeForce()
{
	GetWorld()->GetTimerManager().SetTimer(ForceTimer, this, &APlayerPawn::AddForceMultiply, ChangeForceSpeed, true);
}

void APlayerPawn::AddForceMultiply()
{
	if (!CanMove())
	{
		return;
	}
	ForceMultiply++;

	if (ForceMultiply > MaxForceMultiply)
	{
		Move();
		ForceMultiply = 1.0f;
	}
}

void APlayerPawn::Move()
{
	if (!CanMove())
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(ForceTimer);
	FVector ForceVector = ArrowComponent->GetForwardVector() * ForceMultiply * Force;
	SphereCollision->AddForce(ForceVector, NAME_None, true);
}


void APlayerPawn::RotateRight(float Value)
{
	FRotator ArrowRotation = ArrowComponent->GetRelativeRotation();
	FRotator NewRotation = ArrowRotation + FRotator(0.0f, Value, 0.0f);
	ArrowComponent->SetWorldRotation(FMath::Lerp(NewRotation, ArrowRotation, 0.1f));
}

void APlayerPawn::SpecialAbility()
{
	RotateValue = ArrowComponent->GetRelativeRotation();
	GetWorld()->GetTimerManager().SetTimer(AbilityTimer, this, &APlayerPawn::StartLightning, 0.001f, true, 0.1f);
}

bool APlayerPawn::CanMove()
{
	bool bCanMove = false;

	if (SphereCollision->GetPhysicsLinearVelocity().X > 0.01f)
	{
		bCanMove = false;
	}
	else
	{
		bCanMove = true;
	}

	return bCanMove;
}

void APlayerPawn::StartLightning()
{
	RotateRight(1.0f);

	FHitResult hitResult;
	
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;

	FVector StartPosition = ArrowComponent->GetComponentLocation();
	FVector EndPosition =  ArrowComponent->GetForwardVector() * Radius + StartPosition;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, StartPosition, EndPosition, ECollisionChannel::ECC_Visibility, traceParams))
	{
		DrawDebugLine(GetWorld(), StartPosition, EndPosition, FColor::Red, false, 0.5f, 0, 5);

		if (hitResult.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlap Actor %s"), *hitResult.GetActor()->GetName());
			traceParams.AddIgnoredActor(hitResult.GetActor());
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPosition, EndPosition, FColor::Green, false, 2.0f, 0, 5);
	}
}

