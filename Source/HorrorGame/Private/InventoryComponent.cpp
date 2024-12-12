#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxAmountItem = 10;
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

void UInventoryComponent::AddToInventory(ABaseObject* InventoryItem)
{
	UE_LOG(LogTemp, Warning, TEXT("CALL ADD"));
	
	for (auto& Element : Items)
	{
		if (Element.ItemStack == 0) continue;
		
		if (ShouldStackItem(Element, InventoryItem->Items))
		{
			UE_LOG(LogTemp, Warning, TEXT("CALL ADD SHOULDDDD"));
			Element.ItemStack += InventoryItem->ItemStack;
			UE_LOG(LogTemp, Warning, TEXT("New amount item: %d"),Element.ItemStack);
			InventoryWidget->RefreshInventory(this);
			return;
		}
	}

	if (HasSpaceInventory(InventoryItem->ItemStack))
	{
		UE_LOG(LogTemp, Warning, TEXT("CALL ADD ITEM"));
		FStructItem NewItem;
		NewItem.ItemName = InventoryItem->ItemName;
		NewItem.ItemDescription = InventoryItem->ItemDescription;
		NewItem.ItemImage = InventoryItem->ItemIcon;
		NewItem.ItemStack = InventoryItem->ItemStack;
		NewItem.bIsStackable = InventoryItem->bIsStackable;
		Items.Insert(NewItem, ItemIndex);
		Items.RemoveAt(InventorySlot - ItemIndex);
		InventoryWidget->RefreshInventory(this);
	}
}

bool UInventoryComponent::ShouldStackItem(FStructItem& ItemInventory, FStructItem& ItemToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("CALL SHOULD"));
	bool bIsInventory = ItemToAdd.bItemInventory;
	bool bIsStackable = ItemToAdd.bIsStackable;
	bool bHasPlaceStack = (ItemInventory.ItemStack + ItemToAdd.ItemStack) <= MaxAmountItem;
	bool bIsSameItem = ItemInventory.ItemName.ToString() == ItemToAdd.ItemName.ToString();
	UE_LOG(LogTemp, Warning, TEXT("bIsInventory: %d, bIsStackable: %d, bHasPlaceStack: %d, bIsSameItem: %d"),
	   bIsInventory, bIsStackable, bHasPlaceStack, bIsSameItem);
	if (bIsInventory && bIsStackable && bHasPlaceStack && bIsSameItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("CALL TRUE"));
		NewAmountItem = ItemInventory.ItemStack + ItemToAdd.ItemStack;
		UE_LOG(LogTemp, Warning, TEXT("New amount item: %d"), NewAmountItem);
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("CALL FALSE"));
	NewAmountItem = ItemInventory.ItemStack;
	UE_LOG(LogTemp, Warning, TEXT("New amount item: %d"), NewAmountItem);
	return false;
}

bool UInventoryComponent::HasSpaceInventory(int32 ItemAmountFromInventory)
{
	UE_LOG(LogTemp, Warning, TEXT("CALL SPACE"));
	if (ItemAmountFromInventory == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CALL SPACE FALSE"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("CALL SPACE TRUE"));
	return true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UInventoryWidget* Widget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	InventoryWidget = Cast<UInventoryWidget>(Widget);

	Items.SetNum(InventorySlot);
	Widget->RefreshInventory(this);
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
