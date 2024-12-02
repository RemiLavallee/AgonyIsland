// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "ItemSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

void UInventoryWidget::RefreshInventory(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent)
	{
		WrapInventory->ClearChildren();
		int32 Index = 0;
		for (auto& Element : InventoryComponent->Items)
		{
			if (UItemSlotWidget* Widget = CreateWidget<UItemSlotWidget>(GetWorld(), SlotWidgetClass))
			{
				// InventoryComponent->Items;
				Widget->Item = Element;
				Widget->Index = Index;
				Widget->InventoryWidget = this;
				Widget->RefreshSlot(Element);
				WrapInventory->AddChildToWrapBox(Widget);
			}
			Index++;
		}
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NameText->SetText(InventoryName);
	DescriptionText->SetText(InventoryDescription);
}

void UInventoryWidget::UpdateText()
{
	if (NameText)
	{
		NameText->SetText(InventoryName);
	}

	if (DescriptionText)
	{
		DescriptionText->SetText(InventoryDescription);
	}
}


FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::I)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetShowMouseCursor(false);
		FInputModeGameOnly InputModeG;
		PlayerController->SetInputMode(InputModeG);
		RemoveFromParent();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
