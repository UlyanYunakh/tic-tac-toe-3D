// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameMode.generated.h"


UCLASS()
class TICTACTOE3D_API ATicTacToeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGameBoard();

protected:
	class UTicTacToeBoard* GameBoard;
	
};
