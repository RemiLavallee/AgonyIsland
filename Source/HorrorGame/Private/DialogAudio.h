#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogAudio.generated.h"

USTRUCT(BlueprintType)
struct FDialogAudio : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* DialogAudio;
};