// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObject.h"

// Sets default values
ABaseObject::ABaseObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(Root);
	
	bIsPickedUp = false;
	AttachedComponent = nullptr;
}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	InitializeFromDataTable();
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (bIsPickedUp && AttachedComponent)
	{
		SetActorLocation(AttachedComponent->GetComponentLocation());
		SetActorRotation(AttachedComponent->GetComponentRotation());
	}
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

void ABaseObject::DropItem()
{
}

void ABaseObject::PickUp(USceneComponent* AttachTo)
{
	if (!AttachTo) return;

	AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetIncludingScale);
	AttachedComponent = AttachTo;

	StaticMeshComp->SetSimulatePhysics(false);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsPickedUp = true;
}

void ABaseObject::Drop(const FVector& DropLocation)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SetActorLocation(DropLocation);
	bIsPickedUp = false;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetObject, this, &ABaseObject::ResetObjectProperties, 0.5f, false);
}

void ABaseObject::InitializeFromDataTable()
{
	static const FString Context = TEXT("Object Initialization");
	FStructObjectData* Row = DataTable->FindRow<FStructObjectData>(RowName, Context);

	if (Row->Mesh)
	{
		StaticMeshComp->SetStaticMesh(Row->Mesh);
	}

	ActiveInterface = EInterfaceType::None;
	ActiveInterface = Row->InterfaceType;

	switch (ActiveInterface)
	{
	case Row->InterfaceType == EInterfaceType::Pickup:
		ActiveInterface = EInterfaceType::Pickup;
		break;

	case Row->InterfaceType == EInterfaceType::Inspect:
		ActiveInterface = EInterfaceType::Inspect;
		break;

	case Row->InterfaceType == EInterfaceType::Interact:
		ActiveInterface = EInterfaceType::Interact;
		break;

	default:
		break;
	}
}

void ABaseObject::AssignMeshFromDataTable()
{
	static const FString ContextString(TEXT("Mesh Data Context"));
	FStructObjectData* Row = DataTable->FindRow<FStructObjectData>(RowName, ContextString);

	StaticMeshComp->SetStaticMesh(Row->Mesh);
}

void ABaseObject::ResetObjectProperties()
{
	StaticMeshComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMeshComp->SetSimulatePhysics(false);
}
