// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


UCLASS()
class UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RefreshInventory(class UInventoryComponent* InventoryComponent);

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapInventory;

	UPROPERTY()
	class UItemSlotWidget* SlotWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemSlotWidget> SlotWidgetClass;

	protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
