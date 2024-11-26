// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LetterWidget.generated.h"

/**
 * 
 */
UCLASS()
class ULetterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ReadButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;
	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBoxText;

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnReadButton();
	UFUNCTION()
	void OnCloseButton();
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DescriptionText;
};
