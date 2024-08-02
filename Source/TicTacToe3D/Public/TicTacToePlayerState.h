// Ullian Yunakh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TicTacToeTypes.h"
#include "TicTacToePlayerState.generated.h"

DECLARE_DELEGATE(FOnTurnStarted);
DECLARE_DELEGATE(FOnTurnEnded);

UCLASS()
class TICTACTOE3D_API ATicTacToePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	FORCEINLINE EBoardCellStatus GetPlayerFlag() { return PlayerFlag; }
	FORCEINLINE void SetPlayerFlag(EBoardCellStatus NewFlag) { PlayerFlag = NewFlag; }

protected:
	EBoardCellStatus PlayerFlag;

public:
	UFUNCTION(Client, Reliable)
	virtual void StartTurn();
	virtual void StartTurn_Implementation();

	UFUNCTION(Client, Reliable)
	virtual void EndTurn();
	virtual void EndTurn_Implementation();

	FOnTurnStarted OnTurnStarted;
	FOnTurnEnded OnTurnEnded;
};
