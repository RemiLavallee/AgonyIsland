#include "Portal.h"
#include "NiagaraComponent.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(Root);

	EffectNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EffectNiagara"));
	EffectNiagara->SetupAttachment(Root);
}

void APortal::OnInteract()
{
	Super::OnInteract();
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	EffectNiagara->Deactivate();
}

void APortal::ActivatePortal()
{
	EffectNiagara->Activate();
}