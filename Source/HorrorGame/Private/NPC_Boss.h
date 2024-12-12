#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_Boss.generated.h"

UCLASS()
class ANPC_Boss : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC_Boss();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* HitAnimMontage;

	UPROPERTY(visibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;
};
