// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObject.h"

// Sets default values
ABaseObject::ABaseObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComp;

}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("BeginPlay called for: %s, RowName: %s"), *GetName(), *RowName.ToString());
	InitializeFromDataTable();
	
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseObject::OnPickUp()
{
}

void ABaseObject::OnInspect()
{
}

void ABaseObject::OnInteract()
{
}

void ABaseObject::InitializeFromDataTable()
{
	
	static const FString Context = TEXT("Object Initialization");
	FStructObjectData* Row = DataTable->FindRow<FStructObjectData>(RowName, Context);

	if (Row->Mesh)
	{
		UStaticMeshComponent* MeshComp = FindComponentByClass<UStaticMeshComponent>();
		if (MeshComp)
		{
			MeshComp->SetStaticMesh(Row->Mesh);
		}
	}

	ActiveInterface = EInterfaceType::None;
	ActiveInterface = Row->InterfaceType;
	
	switch (ActiveInterface)
	{
	case EInterfaceType::Pickup:
		UE_LOG(LogTemp, Log, TEXT("Object set as Pickup"));
		ActiveInterface = EInterfaceType::Pickup;
		break;

	case EInterfaceType::Inspect:
		UE_LOG(LogTemp, Log, TEXT("Object set as Inspect"));
		ActiveInterface = EInterfaceType::Inspect;

		break;

	default:
		UE_LOG(LogTemp, Log, TEXT("No interface set for this object"));
		break;
	}
	
}

void ABaseObject::AssignMeshFromDataTable()
{
	static const FString ContextString(TEXT("Mesh Data Context"));
	FStructObjectData* Row = DataTable->FindRow<FStructObjectData>(RowName, ContextString);
	
	StaticMeshComp->SetStaticMesh(Row->Mesh);
}
