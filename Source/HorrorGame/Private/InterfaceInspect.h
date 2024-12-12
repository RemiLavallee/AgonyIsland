#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceInspect.generated.h"

UINTERFACE(MinimalAPI)
class UInterfaceInspect : public UInterface
{
	GENERATED_BODY()
};

class IInterfaceInspect
{
	GENERATED_BODY()

public:
	virtual void OnInspect() = 0;
};
