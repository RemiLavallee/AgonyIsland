// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructItem.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


UCLASS()
class UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RefreshInventory(class UInventoryComponent* InventoryComponent);
	virtual void NativeConstruct() override;
	void UpdateText();
	
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapInventory;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

	FText InventoryName;
	FText InventoryDescription;

	UPROPERTY()
	class UItemSlotWidget* SlotWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemSlotWidget> SlotWidgetClass;

	protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
