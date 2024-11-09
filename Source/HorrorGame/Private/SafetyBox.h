// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "SafetyBox.generated.h"

/**
 * 
 */
UCLASS()
class ASafetyBox : public ABaseObject
{
	GENERATED_BODY()
public:
	ASafetyBox();

public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SafetyBoxMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SafetyBoxDoorBlockMesh;
};
