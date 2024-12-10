#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "PillarPuzzle.generated.h"

UCLASS()
class APillarPuzzle : public ABaseObject
{
	GENERATED_BODY()

public:
	APillarPuzzle();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PillarMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GlyphMesh;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* EffectNiagara;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pillar Combinaison")
	int PillarIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pillar Combinaison")
	bool ballPillarsActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pillar Combinaison")
	class APillarCombination* PillarCombination;

	virtual void OnInteract() override;
	virtual void BeginPlay() override;
	void ActivatePillar(int Index);
	void DeactivatePillar(int Index);
};
