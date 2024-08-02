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
	virtual void HandleMatchHasStarted() override;

public:
	virtual void SelectFirstActivePlayer();
	virtual void SelectNextActivePlayer();

	FORCEINLINE APlayerState* GetActivePlayerRef() { return ActivePlayerRef; }

private:
	void UpdateActivePlayerRef();

	UPROPERTY()
	APlayerState* ActivePlayerRef;

	uint32 ActivePlayerIndex;

private:
	void InitNonSpectatorPlayersArray();

	UPROPERTY()
	TArray<TObjectPtr<APlayerState>> NonSpectatorPlayers;

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
