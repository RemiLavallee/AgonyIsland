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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Objects")
	FName RowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Objects")
	UDataTable* DataTable;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	virtual void OnPickUp() override;
	virtual void OnInspect() override;
	virtual void OnInteract() override;

	EInterfaceType ActiveInterface;

private:
	void InitializeFromDataTable();
	
	UFUNCTION(CallInEditor, Category = "Objects")
	void AssignMeshFromDataTable();
};
