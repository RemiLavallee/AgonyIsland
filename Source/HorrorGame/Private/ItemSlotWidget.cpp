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
		UE_LOG(LogTemp, Warning, TEXT("Text set: %s"), *StackText.ToString());
		ItemCountBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ItemCountBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	Item = NewItem;
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
		if (Item.ItemName.ToString() == TEXT("Default Name"))
		{
			InventoryWidget->InventoryName = FText::GetEmpty();
			InventoryWidget->InventoryDescription = FText::GetEmpty();
		}
		else
		{
			InventoryWidget->InventoryName = Item.ItemName;
			InventoryWidget->InventoryDescription = Item.ItemDescription;
		}
		InventoryWidget->UpdateText(); 
	}
}

void UItemSlotWidget::OnButtonUnHovered()
{
	if (IsValid(InventoryWidget))
	{
		InventoryWidget->InventoryName.GetEmpty();
		InventoryWidget->InventoryDescription.GetEmpty();
		InventoryWidget->UpdateText(); 
	}
}
