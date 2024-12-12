#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LetterWidget.generated.h"

UCLASS()
class ULetterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnClose();
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DescriptionText;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* ObjectImage;
};
