#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "StructItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	
	void OpenWidget();
	void AddToInventory(ABaseObject* InventoryItem);
	bool ShouldStackItem(FStructItem& ItemInventory, FStructItem& ItemToAdd);
	bool HasSpaceInventory(int32 ItemAmountFromInventory);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class UInventoryWidget* InventoryWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<FStructItem> Items;
	int ItemIndex;
	int MaxAmountItem;
	int InventorySlot;
	int NewAmountItem;
};
