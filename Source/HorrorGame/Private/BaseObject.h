// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructObjectData.h"
#include "InterfaceInspect.h"
#include "InterfaceInteract.h"
#include "InterfacePickUp.h"
#include "BaseObject.generated.h"

UCLASS()
class ABaseObject : public AActor, public IInterfaceInspect, public IInterfacePickUp, public IInterfaceInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	USceneComponent* AttachedComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Objects")
	FName RowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Objects")
	UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
	TSubclassOf<AActor> AssociatedBlueprint;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	virtual void OnPickUp() override;
	virtual void OnInspect() override;
	virtual void OnInteract() override;
	virtual void DropItem();
	virtual void PickUp(USceneComponent* AttachTo);
	virtual void Drop(const FVector& DropLocation);
	

	EInterfaceType ActiveInterface;
	bool bIsPickedUp;

private:
	void InitializeFromDataTable();
	
	UFUNCTION(CallInEditor, Category = "Objects")
	void AssignMeshFromDataTable();

	FTimerHandle TimerHandle_ResetObject;
	void ResetObjectProperties();
};
