#include "MainMenuWidget.h"
#include "SafetyBoxWidget.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AudioComponent = UGameplayStatics::SpawnSound2D(this, MainMenuSound, 1.f);

	PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) SetInputModeUI(PlayerController);
	
	PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayButton);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsButton);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButton);
	BackButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnBackButton);

	SliderSound->OnValueChanged.AddDynamic(this, &UMainMenuWidget::OnSoundValueChanged);
	SliderSound->SetValue(1.f);
	SliderSensibility->OnValueChanged.AddDynamic(this, &UMainMenuWidget::OnSensibilityValueChanged);
	SliderSensibility->SetValue(1.f);
}

void UMainMenuWidget::OnPlayButton()
{
	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
	OpenLevel();
}

void UMainMenuWidget::OnOptionsButton()
{
	PanelOptions->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::OnExitButton()
{
	if (PlayerController) UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnBackButton()
{
	PanelOptions->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuWidget::SetInputModeUI(APlayerController* PlayerControl)
{
	if (!PlayerControl) return;

	FInputModeUIOnly InputMode;
	PlayerControl->SetInputMode(InputMode);
	PlayerControl->bShowMouseCursor = true;
}

void UMainMenuWidget::OpenLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UMainMenuWidget::OnSoundValueChanged(float Value)
{
	SetSoundVolume(Value);
}

void UMainMenuWidget::SetSoundVolume(float Value)
{
	AudioComponent->SetVolumeMultiplier(FMath::Clamp(Value, 0.f, 1.f));
}

void UMainMenuWidget::OnSensibilityValueChanged(float Value)
{
	SetSensibilityValue(Value);
}

void UMainMenuWidget::SetSensibilityValue(float Value)
{
	float ClampedValue = FMath::Clamp(Value, 0.f, 10.f);

	PlayerController->InputYawScale_DEPRECATED = ClampedValue;
	PlayerController->InputPitchScale_DEPRECATED = ClampedValue;
}
