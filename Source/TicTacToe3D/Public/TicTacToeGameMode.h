// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TicTacToeTypes.h"
#include "TicTacToeGameMode.generated.h"

class AChip;
class ATicTacToeGameState;

UCLASS()
class TICTACTOE3D_API ATicTacToeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PlayerMadeMove(int32 PlayerID, TDelegate<void()>& PieceAddedDelegate);

protected:
	virtual void HandleMatchIsWaitingToStart() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	
	virtual void HandleMatchHasStarted() override;

	virtual void FirstPreTurnStart();

	virtual void PreTurnStart();

	virtual void StartTurn();

	virtual void EndTurn();

protected:
	virtual void TurnTimerEnd(APlayerState* PlayerStateRef);

public:
	/* Time before match actually starts */
	UPROPERTY(EditAnywhere, Category="Timers")
	float InitialDelayTime;
	FTimerHandle InitialDelayTimer;

	/* Turn duration time */
	UPROPERTY(EditAnywhere, Category = "Timers")
	float TurnDuration;
};
