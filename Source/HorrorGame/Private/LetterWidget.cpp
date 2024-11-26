// Fill out your copyright notice in the Description page of Project Settings.


#include "LetterWidget.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"

void ULetterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReadButton->OnClicked.AddDynamic(this, &ULetterWidget::OnReadButton);
	CloseButton->OnClicked.AddDynamic(this, &ULetterWidget::OnCloseButton);
}

void ULetterWidget::OnReadButton()
{
	SizeBoxText->SetVisibility(ESlateVisibility::Visible);
}

void ULetterWidget::OnCloseButton()
{
	RemoveFromParent();
}
