#include "NPC_Boss.h"

ANPC_Boss::ANPC_Boss()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPC_Boss::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC_Boss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC_Boss::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	GetMesh()->GetAnimInstance()->Montage_Play(HitAnimMontage);
}

