#include "PillarPuzzle.h"
#include "NiagaraComponent.h"
#include "PillarCombination.h"
#include "Portal.h"

APillarPuzzle::APillarPuzzle()
{
	PillarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PillarMesh"));
	PillarMesh->SetupAttachment(Root);

	GlyphMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlyphMesh"));
	GlyphMesh->SetupAttachment(PillarMesh);

	EffectNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EffectNiagara"));
	EffectNiagara->SetupAttachment(Root);

	ballPillarsActivated = false;
}

void APillarPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	EffectNiagara->Deactivate();
}

void APillarPuzzle::ActivatePillar(int Index)
{
	PillarCombination->PillarActivate.Add(Index);

	PillarCombination->NiagaraEffects.Add(EffectNiagara);
	
	EffectNiagara->Activate();
	
	if (PillarCombination->PillarActivate.Num() == PillarCombination->PillarCombinaison.Num())
	{
		ballPillarsActivated = true;
	}
	else
	{
		ballPillarsActivated = false;
	}
}

void APillarPuzzle::DeactivatePillar(int Index)
{
	PillarCombination->NiagaraEffects[Index]->Deactivate();
	PillarCombination->NiagaraEffects.RemoveAt(Index);
	PillarCombination->PillarActivate.Remove(Index);
}

void APillarPuzzle::OnInteract()
{
	Super::OnInteract();
	
	ActivatePillar(PillarIndex);

	if (ballPillarsActivated)
	{
		if (PillarCombination->PillarActivate == PillarCombination->PillarCombinaison)
		{
			PillarCombination->Portal->ActivatePortal();
		}
		else
		{
			for (int i = PillarCombination->PillarActivate.Num() - 1; i >= 0; --i)
			{
				DeactivatePillar(i);
			}
		}
	}
}
