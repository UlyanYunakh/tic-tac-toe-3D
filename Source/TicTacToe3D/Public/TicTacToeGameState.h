// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TicTacToeGameState.generated.h"

/**
 * Tic Tac Toe 3D GameState.
 */
UCLASS()
class TICTACTOE3D_API ATicTacToeGameState : public AGameState
{
	GENERATED_BODY()

protected:
	virtual void HandleMatchHasStarted() override;

	
};
