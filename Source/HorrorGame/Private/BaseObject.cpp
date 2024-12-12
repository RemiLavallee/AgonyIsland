#include "BaseObject.h"
#include "StructItem.h"

ABaseObject::ABaseObject()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(Root);
	
	AttachedComponent = nullptr;
	DataTable = nullptr;
	bItemInventory = false;
	bIsPickedUp = false;
	ItemStack = 0;
	ActiveInterface = EInterfaceType::None;
}

void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	InitializeFromDataTable();
}

void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsPickedUp && AttachedComponent)
	{
		FVector NewLocation = AttachedComponent->GetComponentLocation();
		FRotator NewRotation = AttachedComponent->GetComponentRotation();
		
		if (!GetActorLocation().Equals(NewLocation) || !GetActorRotation().Equals(NewRotation))
		{
			SetActorLocation(NewLocation);
			SetActorRotation(NewRotation);
		}
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

	StaticMeshComp->SetRelativeRotation(FRotator(0, 0, 0));
	StaticMeshComp->SetRelativeLocation(FVector(0, 0, 0));

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
	FStructItem* Row = DataTable->FindRow<FStructItem>(RowName, Context);

	Items = *Row;
	bItemInventory = Row->bItemInventory;
	ItemName = Row->ItemName;
	ItemDescription = Row->ItemDescription;
	bIsStackable = Row->bIsStackable;
	ItemStack = Row->ItemStack;
	ItemIcon = Row->ItemImage;
	
	if (Row->ItemMesh)
	{
		StaticMeshComp->SetStaticMesh(Row->ItemMesh);
	}

	ActiveInterface = EInterfaceType::None;
	ActiveInterface = Row->InterfaceType;

	switch (ActiveInterface)
	{
	case EInterfaceType::Pickup:
		ActiveInterface = EInterfaceType::Pickup;
		break;

	case EInterfaceType::Inspect:
		ActiveInterface = EInterfaceType::Inspect;
		break;

	case EInterfaceType::Interact:
		ActiveInterface = EInterfaceType::Interact;
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown Interface type"));
		break;
	}
}

void ABaseObject::AssignValueFromDataTable()
{
	static const FString ContextString(TEXT("Mesh Data Context"));
	FStructItem* Row = DataTable->FindRow<FStructItem>(RowName, ContextString);

	StaticMeshComp->SetStaticMesh(Row->ItemMesh);
	bItemInventory = Row->bItemInventory;
	ItemName = Row->ItemName;
	ItemDescription = Row->ItemDescription;
	bIsStackable = Row->bIsStackable;
	ItemStack = Row->ItemStack;
	ItemIcon = Row->ItemImage;
}

void ABaseObject::ResetObjectProperties()
{
	StaticMeshComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMeshComp->SetSimulatePhysics(false);
}