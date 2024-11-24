// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorGameCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "BaseObject.h"
#include "FlashLight.h"
#include "OptionsWidget.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AHorrorGameCharacter

AHorrorGameCharacter::AHorrorGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	InspectOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("InspectOrigin"));
	InspectOrigin->SetupAttachment(RootComponent);
	InspectOrigin->SetRelativeLocation(FVector(40.f, 0.f, 0.f));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;

	ItemOffset = CreateDefaultSubobject<USceneComponent>(TEXT("ItemOffset"));
	ItemOffset->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightHandSocket"));
	ItemOffset->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	CurrentActor = nullptr;
	EquippedItem = nullptr;
	IsMoving = false;
	bIsCrouching = false;
}

void AHorrorGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	auto UserWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
	PlayerWidget = Cast<UPlayerWidget>(UserWidget);
	PlayerWidget->AddToViewport();

	if (CrouchCurve)
	{
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("UpdateCrouchTransition"));

		CrouchTimeline.AddInterpFloat(CrouchCurve, TimelineCallback);

		CrouchTimeline.SetLooping(false);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AHorrorGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::Look);

		EnhancedInputComponent->BindAction(EnterInspectAction, ETriggerEvent::Triggered, this,
		                                   &AHorrorGameCharacter::EnterInspect);

		EnhancedInputComponent->BindAction(ExitInspectAction, ETriggerEvent::Triggered, this,
		                                   &AHorrorGameCharacter::ExitInspect);

		EnhancedInputComponent->BindAction(RotateInspectAction, ETriggerEvent::Triggered, this,
		                                   &AHorrorGameCharacter::RotateInspect);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this,
		                                   &AHorrorGameCharacter::ResetMovementVector);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this,
										   &AHorrorGameCharacter::Interact);

		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered, this,
										   &AHorrorGameCharacter::PickUp);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this,
										   &AHorrorGameCharacter::ToggleCrouch);
		
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::Run);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this,
										   &AHorrorGameCharacter::ResetMovementSpeed);

		EnhancedInputComponent->BindAction(OpenOptionsAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::OpenMenuOptions);

		EnhancedInputComponent->BindAction(DropItemAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::DropItem);

		EnhancedInputComponent->BindAction(ToggleFlashLightAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::ToggleFlashLight);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}


void AHorrorGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	CurrentMovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), CurrentMovementVector.Y);
		AddMovementInput(GetActorRightVector(), CurrentMovementVector.X);
	}
}

void AHorrorGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHorrorGameCharacter::EnterInspect()
{
	if (!IsInspecting && IsValid(CurrentActor))
	{
		ABaseObject* HitObject = Cast<ABaseObject>(CurrentActor);
		
		if (HitObject && HitObject->ActiveInterface == EInterfaceType::Inspect)
		{
			
			IsInspecting = true;

			PlayerWidget->SetPromptInspect(false);
			InspectOrigin->SetRelativeRotation(FRotator::ZeroRotator);
			InitialInspectTransform = HitObject->GetActorTransform();
			HitObject->AttachToComponent(InspectOrigin,
			                                       FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			auto PlayerController = Cast<APlayerController>(GetController());
			auto InputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer());
			InputSubSystem->RemoveMappingContext(DefaultMappingContext);
			InputSubSystem->AddMappingContext(InspectMappingContext, 0);
		}
	}
}

void AHorrorGameCharacter::ExitInspect()
{
	if (IsInspecting)
	{
		IsInspecting = false;

		if (CurrentActor)
		{
			CurrentActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			if (InitialInspectTransform.IsValid())
			{
				CurrentActor->SetActorTransform(InitialInspectTransform);
			}

			CurrentActor = nullptr;
		}

		auto PlayerController = Cast<APlayerController>(GetController());
		auto InputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer());
		InputSubSystem->RemoveMappingContext(InspectMappingContext);
		InputSubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AHorrorGameCharacter::RotateInspect(const FInputActionValue& Value)
{
	if (!IsValid(CurrentActor))
	{
		UE_LOG(LogTemplateCharacter, Warning, TEXT("RotateInspect called but CurrentInspectActor is null!"));
		return;
	}

	FVector2D RotateAxis = Value.Get<FVector2D>();

	FRotator CurrentRotation = CurrentActor->GetActorRotation();

	FRotator InspectRotation;
	InspectRotation.Pitch = RotateAxis.Y;
	InspectRotation.Yaw = RotateAxis.X * -1.0f;
	InspectRotation.Roll = 0.0f;

	FRotator NewRotation = UKismetMathLibrary::ComposeRotators(CurrentRotation, InspectRotation);

	CurrentActor->SetActorRotation(NewRotation);
}

void AHorrorGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsInspecting)
	{
		FHitResult Hit;
		FVector Start = FirstPersonCameraComponent->GetComponentLocation();
		FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * 200.f);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams, CollisionParams) && IsValid(
			Hit.GetActor()))
		{
			ABaseObject* HitObject = Cast<ABaseObject>(Hit.GetActor());
			if (HitObject && !HitObject->Tags.Contains(FName("IgnoreLineTrace")))
			{
				//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 1.f);
				//FString HitActorName = Hit.GetActor()->GetName();
				if (GEngine)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Hit Object: %s"), *HitActorName));
				}
				switch (HitObject->ActiveInterface)
				{
				case EInterfaceType::Inspect:
					CurrentActor = HitObject;
					PlayerWidget->SetPromptInspect(true);
					PlayerWidget->SetPromptPick(false);
					PlayerWidget->SetPromptInteract(false);
					break;

				case EInterfaceType::Pickup:
					CurrentActor = HitObject;
					PlayerWidget->SetPromptPick(true);
					PlayerWidget->SetPromptInspect(false);
					PlayerWidget->SetPromptInteract(false);
					break;

				case EInterfaceType::Interact:
					CurrentActor = HitObject;
					PlayerWidget->SetPromptPick(false);
					PlayerWidget->SetPromptInspect(false);
					PlayerWidget->SetPromptInteract(true);
					break;

				default:
					CurrentActor = nullptr;
					PlayerWidget->SetPromptPick(false);
					PlayerWidget->SetPromptInspect(false);
					PlayerWidget->SetPromptInteract(false);
					break;
				}
			}
		}
		else
		{
			CurrentActor = nullptr;
			PlayerWidget->SetPromptPick(false);
			PlayerWidget->SetPromptInspect(false);
			PlayerWidget->SetPromptInteract(false);
		}
	}

	if (CurrentMovementVector.IsNearlyZero(0.1f))
	{
		if (IsMoving)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Stopping footsteps sound"));
			StopFootstepsSound();
		}
		IsMoving = false;
	}
	else
	{
		if (!IsMoving)
		{
			StartFootstepsSound();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Starting footsteps sound"));
		}
		IsMoving = true;
	}

	if (CrouchTimeline.IsPlaying())
	{
		CrouchTimeline.TickTimeline(DeltaTime);
	}
	
	if (EquippedItem)
	{
		FTransform SocketTransform = Mesh1P->GetSocketTransform(TEXT("RightHandSocket"), RTS_World);

		EquippedItem->SetActorLocation(SocketTransform.GetLocation());
		EquippedItem->SetActorRotation(SocketTransform.GetRotation().Rotator());
		EquippedItem->SetActorScale3D(SocketTransform.GetScale3D());
	}
	
}

void AHorrorGameCharacter::StartFootstepsSound()
{
	if (FootstepSound && !AudioComponent->IsPlaying())
	{
		AudioComponent->SetSound(FootstepSound);
		AudioComponent->Play();
	}
}

void AHorrorGameCharacter::StopFootstepsSound()
{
	if (AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}
}

void AHorrorGameCharacter::ResetMovementVector()
{
	CurrentMovementVector = FVector2D::ZeroVector;
}

void AHorrorGameCharacter::PickUp()
{
	if (!CurrentActor) return;

	ABaseObject* Object = Cast<ABaseObject>(CurrentActor);
	if (Object)
	{
		Object->PickUp(ItemOffset);
		EquippedItem = Object;
		CurrentActor = nullptr;
	}
}

void AHorrorGameCharacter::Interact()
{
	if (IsValid(CurrentActor))
	{
		ABaseObject* HitObject = Cast<ABaseObject>(CurrentActor);
	
		if (HitObject && HitObject->ActiveInterface == EInterfaceType::Interact)
		{
			HitObject->OnInteract();
			CurrentActor = nullptr;
		}
	}
}

void AHorrorGameCharacter::ToggleCrouch()
{
	if (bIsCrouching)
	{
		CrouchTimeline.Reverse();
		GetCharacterMovement()->MaxWalkSpeed = 400.f;
	}
	else
	{
		CrouchTimeline.Play();
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}

	bIsCrouching = !bIsCrouching;
}

void AHorrorGameCharacter::Run()
{
	if(bIsCrouching)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	Mesh1P->SetRelativeLocation(FVector(185.f, 0.f, -186.f));
}

void AHorrorGameCharacter::ResetMovementSpeed()
{
	if(bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.f;
	}
	Mesh1P->SetRelativeLocation(FVector(209.f, 0.f, -142.f));
}

void AHorrorGameCharacter::OpenMenuOptions()
{
	auto UserWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidgetClass);
	OptionsWidget = Cast<UOptionsWidget>(UserWidget);
	OptionsWidget->AddToViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AHorrorGameCharacter::DropItem()
{
	if (!EquippedItem) return;

	FVector Forward = GetActorForwardVector();
	FVector DropLocation = GetActorLocation() + Forward * 100.f;

	EquippedItem->Drop(DropLocation);
	EquippedItem = nullptr;
}

void AHorrorGameCharacter::ToggleFlashLight()
{
	auto FlashLight = Cast<AFlashLight>(EquippedItem);
	UE_LOG(LogTemp, Warning, TEXT("Flashlight toggled"));
	if (FlashLight) FlashLight->ToggleLight();

}

void AHorrorGameCharacter::UpdateCrouchTransition(float Value)
{
	float NewCapsuleHalfHeight = FMath::Lerp(NormalCapsuleHalfHeight, CrouchedCapsuleHalfHeight, Value);
	GetCapsuleComponent()->SetCapsuleHalfHeight(NewCapsuleHalfHeight);

	float NewCameraHeight = FMath::Lerp(NormalCameraHeight, CrouchedCameraHeight, Value);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, NewCameraHeight));
}


