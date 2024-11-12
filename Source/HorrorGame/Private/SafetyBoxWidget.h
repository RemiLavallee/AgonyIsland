// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SafetyBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class USafetyBoxWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* FirstUpButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* FirstDownButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* SecondUpButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* SecondDownButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ThirdUpButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ThirdDownButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* UnlockButton;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FirstCodeText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SecondCodeText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ThirdCodeText;
public:
	
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnDownFirstButton();
	UFUNCTION()
	void OnUpFirstButton();
	UFUNCTION()
	void OnDownSecondButton();
	UFUNCTION()
	void OnUpSecondButton();
	UFUNCTION()
	void OnDownThirdButton();
	UFUNCTION()
	void OnUpThirdButton();
	UFUNCTION()
	void OnUnlockButton();
	
	void UpdateFirstText(UTextBlock* Text);
	void UpdateSecondtText(UTextBlock* Text);
	void UpdateThirdText(UTextBlock* Text);
	void SetInputModeGameOnly(APlayerController* PlayerController);

	int FirstCounter;
	int SecondCounter;
	int ThirdCounter;
	int CombinaisonCode;
};
