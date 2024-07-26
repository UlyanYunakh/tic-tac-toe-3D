// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TicTacToePlayerController.generated.h"

class AColumn;
class UInputMappingContext;
class UInputAction;

UCLASS()
class TICTACTOE3D_API ATicTacToePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATicTacToePlayerController();
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void PlaceChip();

private:
	void DoCursorLineTrace();

private:
	UPROPERTY()
	AColumn* ActiveColumn;

};
