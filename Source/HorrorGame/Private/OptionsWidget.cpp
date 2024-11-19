// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) SetInputModeUI(PlayerController);

	ResumeButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnResumeButton);
	OptionsButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnOptionsButton);
	MenuButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnOptionsButton);
	BackButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnBackButton);

	SliderSound->OnValueChanged.AddDynamic(this, &UOptionsWidget::OnSoundValueChanged);
	SliderSound->SetValue(1.f);
	SliderSensibility->OnValueChanged.AddDynamic(this, &UOptionsWidget::OnSensibilityValueChanged);
	SliderSensibility->SetValue(1.f);
}

void UOptionsWidget::OnResumeButton()
{
	this->RemoveFromParent();
	SetInputModeGame(PlayerController);
}

void UOptionsWidget::OnOptionsButton()
{
	PanelOptions->SetVisibility(ESlateVisibility::Visible);
}

void UOptionsWidget::OnMenuButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UOptionsWidget::OnBackButton()
{
	PanelOptions->SetVisibility(ESlateVisibility::Hidden);
}

void UOptionsWidget::SetInputModeUI(APlayerController* PlayerControl)
{
	if (!PlayerControl) return;

	FInputModeUIOnly InputMode;
	PlayerControl->SetInputMode(InputMode);
	PlayerControl->bShowMouseCursor = true;
}

void UOptionsWidget::SetInputModeGame(APlayerController* PlayerControl)
{
	if (!PlayerControl) return;

	FInputModeGameOnly InputMode;
	PlayerControl->SetInputMode(InputMode);
	PlayerControl->bShowMouseCursor = false;
}

void UOptionsWidget::OnSoundValueChanged(float Value)
{
	SetSoundVolume(Value);
}

void UOptionsWidget::SetSoundVolume(float Value)
{
	float ClampedValue = FMath::Clamp(Value, 0.f, 1.f);

	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SoundClass, ClampedValue, 1.f, 0.f, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}

void UOptionsWidget::OnSensibilityValueChanged(float Value)
{
	SetSensibilityValue(Value);
}

void UOptionsWidget::SetSensibilityValue(float Value)
{
	float ClampedValue = FMath::Clamp(Value, 0.f, 10.f);

	PlayerController->InputYawScale_DEPRECATED = ClampedValue;
	PlayerController->InputPitchScale_DEPRECATED = -ClampedValue;
}
