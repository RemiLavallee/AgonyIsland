#include "Portal.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "NiagaraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sections/MovieSceneParticleSection.h"

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

	NextPortal->ActivatePortal();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	PlayerCharacter->SetActorLocation(TeleportLocation);
	PlayerCharacter->SetActorRotation(TeleportRotation);

	EffectNiagara->Deactivate();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APortal::DeactivateNextPortal, 5.0f, false);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	ActiveInterface = EInterfaceType::None;
	EffectNiagara->Deactivate();
}

void APortal::ActivatePortal()
{
	ActiveInterface = EInterfaceType::Interact;
	EffectNiagara->Activate();
}

void APortal::DeactivateNextPortal()
{
	NextPortal->EffectNiagara->Deactivate();
}
