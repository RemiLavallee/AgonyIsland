// Fill out your copyright notice in the Description page of Project Settings.


#include "SafetyBox.h"
#include "SafetyBoxWidget.h"
#include "Blueprint/UserWidget.h"

ASafetyBox::ASafetyBox()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SafetyBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SafetyBox"));
	SafetyBoxMesh->SetupAttachment(Root);
	
	SafetyBoxDoorBlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	SafetyBoxDoorBlockMesh->SetupAttachment(Root);
	
}

void ASafetyBox::OnInteract()
{
	Super::OnInteract();
	auto UserWidget = CreateWidget<UUserWidget>(GetWorld(), SafetyBoxWidgetClass);
	SafetyBoxWidget = Cast<USafetyBoxWidget>(UserWidget);
	if (SafetyBoxWidget)
	{
		SafetyBoxWidget->AddToViewport();
	}
	Open();
}

void ASafetyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DoorTimeline.TickTimeline(DeltaTime);
	if (DoorLocationTimeline.IsPlaying())
	{
		DoorLocationTimeline.TickTimeline(DeltaTime);
	}
}

void ASafetyBox::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineFloat DoorUpdateCallback;
	DoorUpdateCallback.BindUFunction(this, FName("UpdateDoorRotation"));

	FOnTimelineFloat LocationUpdateCallback;
	LocationUpdateCallback.BindUFunction(this, FName("UpdateDoorLocation"));

	if(DoorRotationCurve)
	{
		DoorTimeline.AddInterpFloat(DoorRotationCurve, DoorUpdateCallback);
	}
	
	if(DoorLocationCurve)
	{
		DoorLocationTimeline.AddInterpFloat(DoorLocationCurve, LocationUpdateCallback);
	}
}

void ASafetyBox::UpdateDoorRotation(float Value)
{
	FRotator NewRotation = FRotator(0.0f, Value, 0.0f);
	SafetyBoxDoorBlockMesh->SetRelativeRotation(NewRotation);
}

void ASafetyBox::UpdateDoorLocation(float Value)
{
	FVector NewLocation = FVector(Value, 0.0f, 0.0f);
	SafetyBoxDoorBlockMesh->SetRelativeLocation(NewLocation);
}

void ASafetyBox::Open()
{
	DoorTimeline.Play();
	DoorLocationTimeline.Play();

	ActiveInterface = EInterfaceType::None;

	SetActorEnableCollision(false);
	Tags.Add(FName("IgnoreLineTrace"));
}
