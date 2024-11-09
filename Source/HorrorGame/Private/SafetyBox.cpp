// Fill out your copyright notice in the Description page of Project Settings.


#include "SafetyBox.h"

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