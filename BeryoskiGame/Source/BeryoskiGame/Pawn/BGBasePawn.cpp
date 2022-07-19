// Fill out your copyright notice in the Description page of Project Settings.


#include "BGBasePawn.h"
#include "Components\SphereComponent.h"
#include "Components\StaticMeshComponent.h"
#include "AbilitySystem\BGAbilitySystemComponent.h"
#include "AbilitySystem\AttributeSet\BGPawnAttributeSet.h"


ABGBasePawn::ABGBasePawn()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SphereMesh->SetupAttachment(SphereCollision);

	AbilitySystemComponent = CreateDefaultSubobject<UBGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	AttributeSet = CreateDefaultSubobject<UBGPawnAttributeSet>(TEXT("AttributeSet"));
}

void ABGBasePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitGameplayAbilitySystem(NewController);
}

UAbilitySystemComponent* ABGBasePawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABGBasePawn::InitGameplayAbilitySystem(AController* NewController)
{
	AbilitySystemComponent->InitAbilityActorInfo(NewController, this);

	if (!bIsAbilitiesInitialized)
	{
		for (TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass));
		}
		bIsAbilitiesInitialized = true;
	}
}

