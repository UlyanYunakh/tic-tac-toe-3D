// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TicTacToeTypes.h"
#include "TicTacToeGameState.generated.h"

class UTicTacToeBoard;

UCLASS()
class TICTACTOE3D_API ATicTacToeGameState : public AGameState
{
	GENERATED_BODY()

public:
	ATicTacToeGameState();

protected:
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;

protected:
	virtual uint32 SelectFirstPlayer();
	virtual uint32 SelectNextPlayer();

	virtual void InitiateTurnForPlayer(uint32 PlayerID);
	virtual void StartTurn();
	virtual void EndTurn();

public:
	FORCEINLINE uint32 GetActivePlayerID() { return  ActivePlayerID; }

private:
	uint32 ActivePlayerID;

protected:
	virtual void StartTurnCountdown();
	virtual void StartTurnTimer();

	FTimerHandle TurnCountdown;
	FTimerHandle TurnTimer;

	UPROPERTY(EditAnywhere, Category = "Timers", meta = (AllowPrivateAccess = "true"))
	float TurnCountdownTime;

	UPROPERTY(EditAnywhere, Category = "Timers", meta = (AllowPrivateAccess = "true"))
	float TurnTime;

public:
	FORCEINLINE UTicTacToeBoard* GetBoardRef() { return BoardRef; }

private:
	UPROPERTY()
	UTicTacToeBoard* BoardRef;
};
