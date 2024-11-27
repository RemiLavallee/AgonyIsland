// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "Letter_Base.generated.h"

/**
 * 
 */
UCLASS()
class ALetter_Base : public ABaseObject
{
	GENERATED_BODY()

public:
	ALetter_Base();
	
	void CloseWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	USceneCaptureComponent2D* SceneCaptureComponent;

private:
	UPROPERTY()
	class ULetterWidget* LetterWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LetterWidgetClass;

	UPROPERTY(EditAnywhere)
	FText LetterText;

	virtual void OnInspect() override;

	bool bIsInspecting = false;
};
