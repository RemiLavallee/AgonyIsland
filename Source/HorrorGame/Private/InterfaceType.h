// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceType.generated.h"

UENUM(BlueprintType)
enum class EInterfaceType : uint8
{
	None UMETA(DisplayName = "None"),
	Pickup UMETA(DisplayName = "Pickup"),
	Inspect UMETA(DisplayName = "Inspect"),
	Interact UMETA(DisplayName = "Interact")
};