#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogText.generated.h"

USTRUCT(BlueprintType)
struct FDialogText : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;
};