#include "FlashLight.h"
#include "Components/SpotLightComponent.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComp"));
	Light->SetupAttachment(StaticMeshComp);

	bIsActive = false;
	Light->SetVisibility(false);
}

void AFlashLight::ToggleLight()
{
	bIsActive = !bIsActive;
	Light->SetVisibility(bIsActive);
}

void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
}