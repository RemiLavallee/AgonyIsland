// Fill out your copyright notice in the Description page of Project Settings.


#include "SafetyBoxWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void USafetyBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FirstCounter = 0;
	SecondCounter = 0;
	ThirdCounter = 0;

	if(FirstUpButton)
	{
		FirstUpButton->OnClicked.AddDynamic(this, &USafetyBoxWidget::OnUpFirstButton);
	}

	if(FirstDownButton)
	{
		FirstDownButton->OnClicked.AddDynamic(this, &USafetyBoxWidget::OnDownFirstButton);
	}

	if(SecondUpButton)
	{
		SecondUpButton->OnClicked.AddDynamic(this, &USafetyBoxWidget::OnUpSecondButton);
	}

	if(SecondDownButton)
	{
		SecondDownButton->OnClicked.AddDynamic(this, &USafetyBoxWidget::OnDownSecondButton);
	}

	if(ThirdUpButton)
	{
		ThirdUpButton->OnClicked.AddDynamic(this, &USafetyBoxWidget::OnUpThirdButton);
	}

	if(ThirdDownButton)
	{
		ThirdDownButton->OnClicked.AddDynamic(this, &USafetyBoxWidget::OnDownThirdButton);
	}

	if(UnlockButton)
	{
		UnlockButton->OnClicked.AddDynamic(this, &USafetyBoxWidget::OnUnlockButton);
	}
}

void USafetyBoxWidget::OnDownFirstButton()
{
	if(FirstCounter <= 0) return;
	FirstCounter--;
	UpdateFirstText(FirstCodeText);
}

void USafetyBoxWidget::OnUpFirstButton()
{
	FirstCounter++;
	UpdateFirstText(FirstCodeText);
}

void USafetyBoxWidget::OnDownSecondButton()
{
	if(SecondCounter <= 0) return;
	SecondCounter--;
	UpdateSecondtText(SecondCodeText);
}

void USafetyBoxWidget::OnUpSecondButton()
{
	SecondCounter++;
	UpdateSecondtText(SecondCodeText);
}

void USafetyBoxWidget::OnDownThirdButton()
{
	if(ThirdCounter <= 0) return;
	ThirdCounter--;
	UpdateThirdText(ThirdCodeText);
}

void USafetyBoxWidget::OnUpThirdButton()
{
	ThirdCounter++;
	UpdateThirdText(ThirdCodeText);
}

void USafetyBoxWidget::OnUnlockButton()
{
	FString Combination = FString::Printf(TEXT("%02d%02d%02d"), FirstCounter, SecondCounter, ThirdCounter);
	
	if(Combination == "020301")
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			SetInputModeGameOnly(PlayerController);
		}
		RemoveFromParent();
	}
}

void USafetyBoxWidget::UpdateFirstText(UTextBlock* Text)
{
	FString FormattedText = FString::Printf(TEXT("%02d"), FirstCounter);
	Text->SetText(FText::FromString(FormattedText));
}

void USafetyBoxWidget::UpdateSecondtText(UTextBlock* Text)
{
	FString FormattedText = FString::Printf(TEXT("%02d"), SecondCounter);
	Text->SetText(FText::FromString(FormattedText));
}


void USafetyBoxWidget::UpdateThirdText(UTextBlock* Text)
{
	FString FormattedText = FString::Printf(TEXT("%02d"), ThirdCounter);
	Text->SetText(FText::FromString(FormattedText));
}

void USafetyBoxWidget::SetInputModeGameOnly(APlayerController* PlayerController)
{
	if (!PlayerController) return;

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}


