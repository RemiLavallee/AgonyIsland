// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include <string>

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemSlotWidget::RefreshSlot(FStructItem Item)
{
	if (Item.ItemImage->IsValidLowLevel())
	{
		InventorySlotImage->SetBrushFromTexture(Item.ItemImage);
	}
	else
	{
		ItemCountBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Item.bIsStackable)
	{
		FText StackText = FText::AsNumber(Item.ItemStack);
		ItemCountText->SetText(StackText);
	}
	else
	{
		ItemCountBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}
