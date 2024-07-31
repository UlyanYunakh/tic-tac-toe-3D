// Ullian Yunakh


#include "TicTacToeFunctionLibrary.h"
#include "TicTacToeBoard.h"

void UTicTacToeFunctionLibrary::GetWinningCondition(TArray<FWinningCondition>& winningConditionArray)
{
	winningConditionArray.Empty();

	for (uint8 j = 0; j < 4; j++)
	{
		for (uint8 i = 0; i < 4; i++)
		{
			FWinningCondition conditionXAxis;
			conditionXAxis.PositionQueue.Add(FBoardCellLocation(j, i, 0));
			conditionXAxis.PositionQueue.Add(FBoardCellLocation(j, i, 1));
			conditionXAxis.PositionQueue.Add(FBoardCellLocation(j, i, 2));
			conditionXAxis.PositionQueue.Add(FBoardCellLocation(j, i, 3));
			winningConditionArray.Add(conditionXAxis);

			FWinningCondition conditionYAxis;
			conditionYAxis.PositionQueue.Add(FBoardCellLocation(j, 0, i));
			conditionYAxis.PositionQueue.Add(FBoardCellLocation(j, 1, i));
			conditionYAxis.PositionQueue.Add(FBoardCellLocation(j, 2, i));
			conditionYAxis.PositionQueue.Add(FBoardCellLocation(j, 3, i));
			winningConditionArray.Add(conditionYAxis);


			FWinningCondition conditionColumn;
			conditionColumn.PositionQueue.Add(FBoardCellLocation(0, j, i));
			conditionColumn.PositionQueue.Add(FBoardCellLocation(1, j, i));
			conditionColumn.PositionQueue.Add(FBoardCellLocation(2, j, i));
			conditionColumn.PositionQueue.Add(FBoardCellLocation(3, j, i));
			winningConditionArray.Add(conditionColumn);
		}

		FWinningCondition conditionDiagonal1;
		conditionDiagonal1.PositionQueue.Add(FBoardCellLocation(j, 0, 0));
		conditionDiagonal1.PositionQueue.Add(FBoardCellLocation(j, 1, 1));
		conditionDiagonal1.PositionQueue.Add(FBoardCellLocation(j, 2, 2));
		conditionDiagonal1.PositionQueue.Add(FBoardCellLocation(j, 3, 3));
		winningConditionArray.Add(conditionDiagonal1);

		FWinningCondition conditionDiagonal2;
		conditionDiagonal2.PositionQueue.Add(FBoardCellLocation(j, 0, 3));
		conditionDiagonal2.PositionQueue.Add(FBoardCellLocation(j, 1, 2));
		conditionDiagonal2.PositionQueue.Add(FBoardCellLocation(j, 2, 1));
		conditionDiagonal2.PositionQueue.Add(FBoardCellLocation(j, 3, 0));
		winningConditionArray.Add(conditionDiagonal2);

		FWinningCondition conditionDiagonal3;
		conditionDiagonal3.PositionQueue.Add(FBoardCellLocation(0, 0, j));
		conditionDiagonal3.PositionQueue.Add(FBoardCellLocation(1, 1, j));
		conditionDiagonal3.PositionQueue.Add(FBoardCellLocation(2, 2, j));
		conditionDiagonal3.PositionQueue.Add(FBoardCellLocation(3, 3, j));
		winningConditionArray.Add(conditionDiagonal3);

		FWinningCondition conditionDiagonal4;
		conditionDiagonal4.PositionQueue.Add(FBoardCellLocation(0, 3, j));
		conditionDiagonal4.PositionQueue.Add(FBoardCellLocation(1, 2, j));
		conditionDiagonal4.PositionQueue.Add(FBoardCellLocation(2, 1, j));
		conditionDiagonal4.PositionQueue.Add(FBoardCellLocation(3, 0, j));
		winningConditionArray.Add(conditionDiagonal4);

		FWinningCondition conditionDiagonal5;
		conditionDiagonal5.PositionQueue.Add(FBoardCellLocation(0, j, 0));
		conditionDiagonal5.PositionQueue.Add(FBoardCellLocation(1, j, 1));
		conditionDiagonal5.PositionQueue.Add(FBoardCellLocation(2, j, 2));
		conditionDiagonal5.PositionQueue.Add(FBoardCellLocation(3, j, 3));
		winningConditionArray.Add(conditionDiagonal5);

		FWinningCondition conditionDiagonal6;
		conditionDiagonal6.PositionQueue.Add(FBoardCellLocation(0, j, 3));
		conditionDiagonal6.PositionQueue.Add(FBoardCellLocation(1, j, 2));
		conditionDiagonal6.PositionQueue.Add(FBoardCellLocation(2, j, 1));
		conditionDiagonal6.PositionQueue.Add(FBoardCellLocation(3, j, 0));
		winningConditionArray.Add(conditionDiagonal6);
	}

	FWinningCondition conditionDiagonal7;
	conditionDiagonal7.PositionQueue.Add(FBoardCellLocation(0, 0, 0));
	conditionDiagonal7.PositionQueue.Add(FBoardCellLocation(1, 1, 1));
	conditionDiagonal7.PositionQueue.Add(FBoardCellLocation(2, 2, 2));
	conditionDiagonal7.PositionQueue.Add(FBoardCellLocation(3, 3, 3));
	winningConditionArray.Add(conditionDiagonal7);

	FWinningCondition conditionDiagonal8;
	conditionDiagonal8.PositionQueue.Add(FBoardCellLocation(0, 3, 3));
	conditionDiagonal8.PositionQueue.Add(FBoardCellLocation(1, 2, 2));
	conditionDiagonal8.PositionQueue.Add(FBoardCellLocation(2, 1, 1));
	conditionDiagonal8.PositionQueue.Add(FBoardCellLocation(3, 0, 0));
	winningConditionArray.Add(conditionDiagonal8);

	FWinningCondition conditionDiagonal9;
	conditionDiagonal9.PositionQueue.Add(FBoardCellLocation(0, 3, 0));
	conditionDiagonal9.PositionQueue.Add(FBoardCellLocation(1, 2, 1));
	conditionDiagonal9.PositionQueue.Add(FBoardCellLocation(2, 1, 2));
	conditionDiagonal9.PositionQueue.Add(FBoardCellLocation(3, 0, 3));
	winningConditionArray.Add(conditionDiagonal9);

	FWinningCondition conditionDiagonal10;
	conditionDiagonal10.PositionQueue.Add(FBoardCellLocation(0, 0, 3));
	conditionDiagonal10.PositionQueue.Add(FBoardCellLocation(1, 1, 2));
	conditionDiagonal10.PositionQueue.Add(FBoardCellLocation(2, 2, 1));
	conditionDiagonal10.PositionQueue.Add(FBoardCellLocation(3, 3, 0));
	winningConditionArray.Add(conditionDiagonal10);
}

float UTicTacToeFunctionLibrary::GetMinimaxScore(UTicTacToeBoard* const BoardRef, const EBoardCellStatus MaxPlayer, const float Depth)
{
	EBoardCellStatus winningPlayer = EBoardCellStatus::Empty;

	if (BoardRef->Evaluate(winningPlayer)) // true if someone is are winner
	{
		return winningPlayer == MaxPlayer ? +10.0f - Depth : -10.0f + Depth;
	}

	return 0.0f;
}


float UTicTacToeFunctionLibrary::Minimax(const FMinimaxPayload& Payload, const float Depth, const bool bMaximizingPlayer, float Alpha, float Beta)
{
	float score = UTicTacToeFunctionLibrary::GetMinimaxScore(Payload.Board, Payload.MaximizingPlayer, Depth);
	if (score != 0.0f) return score; // if score is non zero, it means that somebody has won

	if (Depth >= Payload.MaxDepth) return score;

	TArray<FBoardCellLocation> possibleMoves;
	Payload.Board->GetPossibleMoves(possibleMoves);

	if (bMaximizingPlayer)
	{
		float bestScore = -INFINITY;
		for (FBoardCellLocation& move : possibleMoves)
		{
			Payload.Board->BoardMove(Payload.MaximizingPlayer, move); // do move
			score = UTicTacToeFunctionLibrary::Minimax(Payload, Depth + 1, false, Alpha, Beta);
			Payload.Board->BoardMove(EBoardCellStatus::Empty, move); // undo move

			bestScore = FMath::Max(bestScore, score);
			Alpha = FMath::Max(Alpha, bestScore);
			
			if (Beta <= Alpha) break;
		}

		return bestScore;
	}
	else
	{
		float bestScore = INFINITY;
		for (FBoardCellLocation& move : possibleMoves)
		{
			Payload.Board->BoardMove(Payload.MinimizingPlayer, move); // do move
			score = UTicTacToeFunctionLibrary::Minimax(Payload, Depth + 1, true, Alpha, Beta);
			Payload.Board->BoardMove(EBoardCellStatus::Empty, move); // undo move

			bestScore = FMath::Min(bestScore, score);
			Beta = FMath::Min(Beta, bestScore);

			if (Beta <= Alpha) break;
		}

		return bestScore;
	}
}


FBoardCellLocation UTicTacToeFunctionLibrary::GetCellLocationByColumnID(UTicTacToeBoard* const BoardRef, uint8 ColumnID)
{
	FBoardCellLocation location;
	location.Row = ColumnID >> 2;
	location.Column = ColumnID % 4;

	for (uint8 i = 0; i < 4; i++)
	{
		location.Layer = i;
		uint8 index = location.Layer * 16 + location.Row * 4 + location.Column;

		if (BoardRef->Cells[index].Status == EBoardCellStatus::Empty)
		{
			return location;
		}
	}

	return location;
}
