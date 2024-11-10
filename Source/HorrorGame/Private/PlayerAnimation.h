// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimation.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	UPlayerAnimation();

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Speed;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ACharacter* PlayerCharacter;

	virtual void NativeBeginPlay() override;
};
