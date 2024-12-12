#pragma once

#include "CoreMinimal.h"
#include "StructItem.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.generated.h"

UCLASS()
class UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* InventorySlotImage;

	UPROPERTY(meta = (BindWidget))
	class UButton* ItemButton;

	UPROPERTY(meta = (BindWidget))
	class UBorder* ItemCountBorder;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCountText;

public:
	FStructItem Item;
	int Index;

	UFUNCTION()
	void RefreshSlot(const FStructItem& NewItem);
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnButtonHovered();
	UFUNCTION()
	void OnButtonUnHovered();
	
	UPROPERTY()
	class UInventoryWidget* InventoryWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
};
