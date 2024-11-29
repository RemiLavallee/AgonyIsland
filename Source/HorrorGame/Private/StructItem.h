#pragma once

#include "CoreMinimal.h"
#include "StructItem.generated.h"


USTRUCT(BlueprintType) 
struct FStructItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bItemInventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsStackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UStaticMesh* ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UTexture2D* ItemImage;

	FStructItem()
	: bItemInventory(false)
	, ItemName(FText::FromString("Default Name"))
	, ItemDescription(FText::FromString("Default Description"))
	, bIsStackable(false)
	, ItemStack(0)
	, ItemMesh(nullptr)
	, ItemImage(nullptr)
	{}
};
