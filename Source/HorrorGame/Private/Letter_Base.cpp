// Fill out your copyright notice in the Description page of Project Settings.


#include "Letter_Base.h"

#include "LetterWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

ALetter_Base::ALetter_Base()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALetter_Base::OnInspect()
{
	Super::OnInspect();

	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	auto Widget = CreateWidget<UUserWidget>(GetWorld(), LetterWidgetClass);
	LetterWidget = Cast<ULetterWidget>(Widget);
	if (LetterWidget)
	{
		LetterWidget->AddToViewport();
		LetterWidget->DescriptionText->SetText(LetterText);
	}
}
