// Ullian Yunakh

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TicTacToeTypes.h"
#include "TicTacToefunctionLibrary.generated.h"

class UTicTacToeBoard;

UCLASS()
class TICTACTOE3D_API UTicTacToeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void GetWinningCondition(TArray<FWinningCondition>& winningConditionArray);

	static float GetMinimaxScore(UTicTacToeBoard* const Board, const EBoardCellStatus MaxPlayer, const float Depth);

	static float Minimax(const FMinimaxPayload& Payload, const float Depth, const bool bMaximizingPlayer, float Alpha, float Beta);

	static UTicTacToeBoard* GetGameBoard();

};