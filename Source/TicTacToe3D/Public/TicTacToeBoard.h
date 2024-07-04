// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TicTacToeTypes.h"
#include "TicTacToeBoard.generated.h"


UCLASS()
class TICTACTOE3D_API UTicTacToeBoard : public UObject
{
	GENERATED_BODY()

	UTicTacToeBoard(const FObjectInitializer& ObjectInitializer);

public:
	/*
	* Finds all possible moves on given board
	* @param	Board				Target board
	* @param	PossibleMoves		out param will contain all posible moves (up to 16 moves)
	*/
	void GetPossibleMoves(TArray<FBoardCellLocation>& PossibleMoves);

	/*
	* Move by Player on the board
	* @param	Board			Target board
	* @param	Player			Target player
	* @param	MovePosition	Position, where player made his move
	* @return	bool			return true if move was completed, false otherwise
	*/
	bool BoardMove(const EBoardCellStatus Player, const FBoardCellLocation& MovePosition);

	/*
	* Evaluate board
	* @param	WinningPlayer	Output param, it says who is winning
	* @return	bool			return true if player fully achived winning condition, false otherwise
	*/
	bool Evaluate(EBoardCellStatus& WinningPlayer);

public:
	TArray<FBoardCell> Cells;

private:
	TArray<FWinningCondition> WinningConditions;
	
};
