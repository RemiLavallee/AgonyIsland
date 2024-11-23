// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "Components/SpotLightComponent.h"
#include "FlashLight.generated.h"

/**
 * 
 */
UCLASS()
class AFlashLight : public ABaseObject
{
	GENERATED_BODY()
	
public:
		
	AFlashLight();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FlashLightMesh;

	UPROPERTY(visibleAnywhere, Category = "Light")
	USpotLightComponent* Light;

	void ToggleLight();
	void DisablePhysics();

protected:
	virtual void BeginPlay() override;
	virtual void OnPickUp() override;
	virtual void DropItem() override;

private:
	
	bool bIsActive;
};
