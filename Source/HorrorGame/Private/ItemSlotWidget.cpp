// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include <string>

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemSlotWidget::RefreshSlot(const FStructItem& NewItem)
{
	if (NewItem.ItemImage->IsValidLowLevel())
	{
		InventorySlotImage->SetBrushFromTexture(NewItem.ItemImage);
	}
	else
	{
		ItemCountBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	if (NewItem.bIsStackable)
	{
		FText StackText = FText::AsNumber(NewItem.ItemStack);
		ItemCountText->SetText(StackText);
	}
	else
	{
		ItemCountBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}
