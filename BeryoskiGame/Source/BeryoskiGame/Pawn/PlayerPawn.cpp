// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components\SphereComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Components\ArrowComponent.h"

APlayerPawn::APlayerPawn()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SphereMesh->SetupAttachment(SphereCollision);

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

