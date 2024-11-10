// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "Components/TimelineComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Animation")
	UCurveFloat* DoorRotationCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Animation")
	UCurveFloat* DoorLocationCurve;

	FTimeline DoorTimeline;
	FTimeline DoorLocationTimeline;

	virtual void OnInteract() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateDoorRotation(float Value);
	
	UFUNCTION()
	void UpdateDoorLocation(float Value);
};
