// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include "InventoryWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemSlotWidget::RefreshSlot(const FStructItem& NewItem)
{
	if (IsValid(NewItem.ItemImage))
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

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemButton->OnHovered.AddDynamic(this, &UItemSlotWidget::OnButtonHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UItemSlotWidget::OnButtonUnHovered);
}

void UItemSlotWidget::OnButtonHovered()
{
	if (IsValid(InventoryWidget))
	{
		InventoryWidget->NameText->SetText(Item.ItemName);
		InventoryWidget->DescriptionText->SetText(Item.ItemDescription);
	}
}

void UItemSlotWidget::OnButtonUnHovered()
{
	if (IsValid(InventoryWidget))
	{
		InventoryWidget->NameText->SetText(FText::GetEmpty());
		InventoryWidget->DescriptionText->SetText(FText::GetEmpty());
	}
}
