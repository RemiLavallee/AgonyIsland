// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimation.h"

#include "HorrorGame/HorrorGameCharacter.h"

UPlayerAnimation::UPlayerAnimation() : Speed(0.0f), PlayerCharacter(nullptr)
{}

void UPlayerAnimation::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	APawn* OwningPawn = TryGetPawnOwner();
	if (OwningPawn)
	{
		PlayerCharacter = Cast<AHorrorGameCharacter>(OwningPawn);
	}
}

void UPlayerAnimation::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!PlayerCharacter) return;

	Speed = PlayerCharacter->GetVelocity().Size();

	IsCrouching = PlayerCharacter->IsCrouching();

	if (IsCrouching)
	{
		Speed = 0.0f;
	}
}
