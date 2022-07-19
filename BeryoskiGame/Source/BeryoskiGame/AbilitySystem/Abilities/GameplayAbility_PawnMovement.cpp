// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_PawnMovement.h"
#include "Pawn\PlayerPawn.h"
#include "Components\SphereComponent.h"

bool UGameplayAbility_PawnMovement::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!ActorInfo->AvatarActor->IsA<APlayerPawn>())
	{
		return false;
	}

	APlayerPawn* CachedPawn = StaticCast<APlayerPawn*>(ActorInfo->AvatarActor.Get());
	return CachedPawn->CanMove();
}

void UGameplayAbility_PawnMovement::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	GetWorld()->GetTimerManager().SetTimer(ForceTimer, this, &UGameplayAbility_PawnMovement::AddForceMultiply, ChangeForceSpeed, true);
}

void UGameplayAbility_PawnMovement::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	APlayerPawn* CachedPawn = StaticCast<APlayerPawn*>(ActorInfo->AvatarActor.Get());
	USphereComponent* SphereCollision = CachedPawn->GetRootSphere();

	FVector forwardVector = CachedPawn->GetEyesPosition();
	GetWorld()->GetTimerManager().ClearTimer(ForceTimer);
	FVector ForceVector = forwardVector * ForceMultiply * Force;
	SphereCollision->AddForce(ForceVector, NAME_None, true);

	ForceMultiply = 1;

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGameplayAbility_PawnMovement::AddForceMultiply()
{
	ForceMultiply++;

	if (ForceMultiply > MaxForceMultiply)
	{
		K2_CancelAbility();
	}
}
