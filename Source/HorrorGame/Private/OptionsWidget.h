// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;
	UPROPERTY(meta = (BindWidget))
	UButton* OptionsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MenuButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* PanelOptions;
	UPROPERTY(meta = (BindWidget))
	class USlider* SliderSound;
	UPROPERTY(meta = (BindWidget))
	USlider* SliderSensibility;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FName LevelName;

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnResumeButton();
	UFUNCTION()
	void OnOptionsButton();
	UFUNCTION()
	void OnMenuButton();
	UFUNCTION()
	void OnBackButton();
	void SetInputModeUI(APlayerController* PlayerController);
	void SetInputModeGame(APlayerController* PlayerControl);
	UFUNCTION()
	void OnSoundValueChanged(float Value);
	void SetSoundVolume(float Value);
	UFUNCTION()
	void OnSensibilityValueChanged(float Value);
	void SetSensibilityValue(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundMix* SoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundClass* SoundClass;
};
