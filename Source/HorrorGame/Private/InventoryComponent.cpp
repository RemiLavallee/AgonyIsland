// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxAmountItem = 1;
	InventorySlot = 12;
}

void UInventoryComponent::OpenWidget()
{
	if (!InventoryWidget->IsInViewport())
	{
		InventoryWidget->AddToViewport();
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		InventoryWidget->SetFocus();
		PlayerController->SetInputMode(InputMode);
	}
}

void UInventoryComponent::AddToIventory(ABaseObject* InventoryItem)
{
	int index = 0;
	for (auto Element : InventoryItem)
	{
		index = ItemIndex;
	}
}

void UInventoryComponent::ShouldStackItem(FStructItem ItemInventory, FStructItem ItemToAdd)
{
	if (ItemToAdd.bItemInventory && ItemToAdd.bIsStackable &&
		ItemInventory.ItemStack + ItemToAdd.ItemStack <= MaxAmountItem && ItemToAdd.ItemName == ItemInventory.ItemName)
	{
		
	}
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UInventoryWidget* Widget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	InventoryWidget = Cast<UInventoryWidget>(Widget);

	Items.SetNum(InventorySlot);
	Widget->RefreshInventory(this);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
