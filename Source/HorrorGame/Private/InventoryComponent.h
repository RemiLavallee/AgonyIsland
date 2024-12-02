// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this component's properties
	UInventoryComponent();
	
	void OpenWidget();
	void AddToInventory(ABaseObject* InventoryItem);
	bool ShouldStackItem(FStructItem& ItemInventory, FStructItem& ItemToAdd);
	bool HasSpaceInventory(int32 ItemAmountFromInventory);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	class UInventoryWidget* InventoryWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<FStructItem> Items;
	int ItemIndex;
	int MaxAmountItem;
	int InventorySlot;
	int NewAmountItem;
	
	
};
