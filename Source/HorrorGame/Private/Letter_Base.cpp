#include "Letter_Base.h"
#include "LetterWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/TextBlock.h"

ALetter_Base::ALetter_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(RootComponent);
}

void ALetter_Base::OnInspect()
{
	Super::OnInspect();

	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SceneCaptureComponent->SetRelativeLocation(FVector(-1000001000.0f, 0, 0));
	StaticMeshComp->SetRelativeLocation(FVector(-1000000800.0f, 0, 0));
	
	auto Widget = CreateWidget<UUserWidget>(GetWorld(), LetterWidgetClass);
	LetterWidget = Cast<ULetterWidget>(Widget);
	if (LetterWidget)
	{
		LetterWidget->AddToViewport();
		LetterWidget->DescriptionText->SetText(LetterText);
	}
}

void ALetter_Base::CloseWidget()
{
	SceneCaptureComponent->SetRelativeLocation(FVector::ZeroVector);
	LetterWidget->RemoveFromParent();
	LetterWidget = nullptr;
}
