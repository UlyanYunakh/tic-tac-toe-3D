// Ullian Yunakh.


#include "TicTacToeBoard.h"
#include <TicTacToeFunctionLibrary.h>


UTicTacToeBoard::UTicTacToeBoard(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UTicTacToeFunctionLibrary::GetWinningCondition(WinningConditions);
}


void UTicTacToeBoard::GetPossibleMoves(TArray<FBoardCellLocation>& PossibleMoves)
{
	for (const FBoardCell& cell : Cells)
	{
		if (cell.Status == EBoardCellStatus::Empty)
		{
			// check if move was added (theres only 16 (or lower) possible moves at the time, and player can't add chip on top of the empty cell)
			bool isMoveAdded = (bool)PossibleMoves.FindByPredicate([&](FBoardCellLocation& _position) { 
				return cell.Position.Row == _position.Row && cell.Position.Column == _position.Column; 
				});

			if (!isMoveAdded)
			{
				PossibleMoves.Add(cell.Position);
			}
		}
	}
}


bool UTicTacToeBoard::BoardMove(const EBoardCellStatus Player, const FBoardCellLocation& MovePosition)
{
	const uint16 indexInArray = MovePosition.Layer + MovePosition.Row + MovePosition.Column;

	if (Cells.IsValidIndex(indexInArray))
	{
		Cells[indexInArray].Status = Player;
		
		return true;
	}

	return false;
}


bool UTicTacToeBoard::Evaluate(EBoardCellStatus& WinningPlayer)
{
	uint8 bestCellCount = -INFINITY;

	for (FWinningCondition& winningCondition : WinningConditions)
	{
		EBoardCellStatus player = EBoardCellStatus::Empty;
		uint8 cellsCount = 0;

		for (FBoardCellLocation& cellLocation : winningCondition.PositionQueue)
		{
			const uint16 indexInArray = cellLocation.Layer + cellLocation.Row + cellLocation.Column;
			
			if (Cells.IsValidIndex(indexInArray))
			{	
				if (Cells[indexInArray].Status == EBoardCellStatus::Empty) continue;

				if (player != EBoardCellStatus::Empty && player != Cells[indexInArray].Status)
				{
					cellsCount = -INFINITY;
					break;
				}

				player = Cells[indexInArray].Status;
				cellsCount++;
			}
		}

		if (cellsCount > bestCellCount)
		{
			bestCellCount = cellsCount;
			WinningPlayer = player;

			if (bestCellCount == 4) return true;
		}
	}
	
	return false;
}