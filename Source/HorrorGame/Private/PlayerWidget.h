#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

UCLASS()
class UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void SetPromptPick(bool IsVisible);
	UFUNCTION(BlueprintImplementableEvent)
	void SetPromptInspect(bool IsVisible);
	UFUNCTION(BlueprintImplementableEvent)
	void SetPromptInteract(bool IsVisible);
	
};
