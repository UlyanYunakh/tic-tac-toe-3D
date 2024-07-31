// Ullian Yunakh.


#include "Actors/TicTacToePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TicTacToePlayerController.h"
#include "Actors/Column.h"


ATicTacToePawn::ATicTacToePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	ZoomMin = 300.0f;
	ZoomMax = 600.0f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = ZoomMax;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}


void ATicTacToePawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(PawnMappingContext, 0);
		}
	}
}


void ATicTacToePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATicTacToePawn::OnConstruction(const FTransform& Transform)
{
	if (CameraBoom)
	{
		CameraBoom->TargetArmLength = ZoomMax;
	}
}


void ATicTacToePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		enhancedInputComponent->BindAction(OrbitAction, ETriggerEvent::Triggered, this, &ATicTacToePawn::OrbitTrigered);

		enhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATicTacToePawn::ZoomTrigered);

		enhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &ATicTacToePawn::ClickCompleted);
	}
}


void ATicTacToePawn::OrbitTrigered(const FInputActionValue& Value)
{
	const FVector2D input = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(input.X);
		AddControllerPitchInput(input.Y);
	}
}


void ATicTacToePawn::ZoomTrigered(const FInputActionValue& Value)
{
	const float input = Value.Get<float>();

	const float newLenght = CameraBoom->TargetArmLength + input;
	CameraBoom->TargetArmLength = FMath::Clamp(newLenght, ZoomMin, ZoomMax);
}


void ATicTacToePawn::ClickCompleted(const FInputActionValue& Value)
{
	if (ATicTacToePlayerController* TTT_PC = Cast<ATicTacToePlayerController>(Controller))
	{
		TTT_PC->PlaceChip();
	}
}

