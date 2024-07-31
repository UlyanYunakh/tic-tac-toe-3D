// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TicTacToePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AColumn;

UCLASS()
class TICTACTOE3D_API ATicTacToePawn : public APawn
{
	GENERATED_BODY()

public:
	ATicTacToePawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void OrbitTrigered(const FInputActionValue& Value);

	virtual void ZoomTrigered(const FInputActionValue& Value);

	virtual void ClickCompleted(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* PawnMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* OrbitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ClickAction;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zoom", meta = (ClampMin = 1))
	float ZoomMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zoom", meta = (ClampMin = 1))
	float ZoomMax;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
};
