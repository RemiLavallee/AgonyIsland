#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "Components/SpotLightComponent.h"
#include "FlashLight.generated.h"

UCLASS()
class AFlashLight : public ABaseObject
{
	GENERATED_BODY()
	
public:
		
	AFlashLight();
	
	UPROPERTY(visibleAnywhere, Category = "Light")
	USpotLightComponent* Light;

	void ToggleLight();
	virtual void BeginPlay() override;

private:
	bool bIsActive;
};
