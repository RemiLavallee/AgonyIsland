// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashLight.h"
#include "Components/SpotLightComponent.h"
#include "HorrorGame/HorrorGameCharacter.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	FlashLightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashLightMesh"));
	FlashLightMesh->SetupAttachment(Root);
	
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComp"));
	Light->SetupAttachment(Root);

	bIsActive = false;
	Light->SetVisibility(false);
}

void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
}

void AFlashLight::OnPickUp()
{
	Super::OnPickUp();

	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerCharacter = Cast<AHorrorGameCharacter>(PlayerController->GetPawn());
	PlayerCharacter->PickUpFlashLight(this);
}

void AFlashLight::ToggleLight()
{
	bIsActive = !bIsActive;
	Light->SetVisibility(bIsActive);
}

