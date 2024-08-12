// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "TicTacToeTypes.generated.h"

#define ECC_Pointer ECC_GameTraceChannel1

class UTicTacToeBoard;

UENUM()
enum class EBoardCellStatus : uint8
{
	Empty = 0,
	Player_1,
	Player_2,
};

USTRUCT()
struct FBoardCellLocation
{
	GENERATED_BODY()

	FBoardCellLocation(const uint8 _layer, const uint8 _row, const uint8 _column) : Layer(_layer), Row(_row), Column(_column) { }
	FBoardCellLocation() : FBoardCellLocation(0, 0, 0) { } // this is not neaded, since uint8 default value is 0

	UPROPERTY()
	uint8 Layer;

	UPROPERTY()
	uint8 Row;

	UPROPERTY()
	uint8 Column;
};

USTRUCT()
struct FBoardCell
{
	GENERATED_BODY()

	FBoardCell(const FBoardCellLocation _position, const EBoardCellStatus _status) : Position(_position), Status(_status) { }
	FBoardCell(const FBoardCellLocation _position) : FBoardCell(_position, EBoardCellStatus::Empty) { }
	FBoardCell() :FBoardCell(FBoardCellLocation(), EBoardCellStatus::Empty) { }

	UPROPERTY()
	FBoardCellLocation Position;

	UPROPERTY()
	EBoardCellStatus Status;

};

USTRUCT()
struct FWinningCondition
{
	GENERATED_BODY()

	FWinningCondition(const TArray<FBoardCellLocation> _positionQueue) :PositionQueue(_positionQueue) { }
	FWinningCondition() : FWinningCondition(TArray<FBoardCellLocation>()) { }

	UPROPERTY()
	TArray<FBoardCellLocation> PositionQueue;
};

USTRUCT()
struct FMinimaxPayload
{
	GENERATED_BODY()

	UPROPERTY()
	UTicTacToeBoard* Board;

	UPROPERTY()
	EBoardCellStatus MaximizingPlayer;

	UPROPERTY()
	EBoardCellStatus MinimizingPlayer;

	UPROPERTY()
	FBoardCellLocation BestMove;

	UPROPERTY()
	uint8 MaxDepth;
};