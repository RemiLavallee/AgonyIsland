#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceInteract.generated.h"

UINTERFACE(MinimalAPI)
class UInterfaceInteract : public UInterface
{
	GENERATED_BODY()
};

class IInterfaceInteract
{
	GENERATED_BODY()

public:
	virtual void OnInteract() = 0;
};
