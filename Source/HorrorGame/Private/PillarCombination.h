#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PillarCombination.generated.h"

UCLASS()
class APillarCombination : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APillarCombination();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pillar Combinaison")
	TArray<int> PillarCombinaison;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pillar Combinaison")
	TArray<int> PillarActivate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pillar Combinaison")
	TArray<class UNiagaraComponent*> NiagaraEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pillar Combinaison")
	class APortal* Portal;
};
