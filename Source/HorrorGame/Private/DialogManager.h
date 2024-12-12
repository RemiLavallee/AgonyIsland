#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogManager.generated.h"

UCLASS()
class ADialogManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADialogManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	UDataTable* DataTable;
	
	UAudioComponent* AudioComponent;
};
