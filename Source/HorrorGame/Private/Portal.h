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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	FVector TeleportLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	FRotator TeleportRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	APortal* NextPortal;

	virtual void OnInteract() override;
	virtual void BeginPlay() override;
	void ActivatePortal();

private:
	FTimerHandle TimerHandle;

	void DeactivateNextPortal();
};
