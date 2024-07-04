// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TicTacToePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE3D_API ATicTacToePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
};
