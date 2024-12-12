#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfacePickUp.generated.h"

UINTERFACE(MinimalAPI)
class UInterfacePickUp : public UInterface
{
	GENERATED_BODY()
};

class IInterfacePickUp
{
	GENERATED_BODY()
public:
	virtual void OnPickUp() = 0;
};
