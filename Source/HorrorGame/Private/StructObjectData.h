#pragma once

#include "CoreMinimal.h"
#include "InterfaceType.h"
#include "Engine/DataTable.h"
#include "StructObjectData.generated.h"

USTRUCT(BlueprintType)
struct FStructObjectData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh = nullptr;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInterfaceType InterfaceType = EInterfaceType::None;
	
};