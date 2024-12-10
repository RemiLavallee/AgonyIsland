#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class APortal : public ABaseObject
{
	GENERATED_BODY()
	
public:	
	APortal();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PortalMesh;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* EffectNiagara;

	virtual void OnInteract() override;
	virtual void BeginPlay() override;

	void ActivatePortal();
};
