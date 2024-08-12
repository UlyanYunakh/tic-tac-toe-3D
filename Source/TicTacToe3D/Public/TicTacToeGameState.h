// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TicTacToeTypes.h"
#include "TicTacToeGameState.generated.h"

DECLARE_DELEGATE_OneParam(FOnTurnTimerEnd, APlayerState* /* Player ref */);

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

private:
	void UpdateActivePlayerRef(bool bFirstPlayer = false);

private:
	void InitNonSpectatorPlayersArray();

	UPROPERTY()
	TArray<TObjectPtr<APlayerState>> NonSpectatorPlayers;

public:
	virtual void StartTurnTimer(const float TurnDuration);
	virtual void ClearTurnTimer();

	FOnTurnTimerEnd OnTurnTimerEnd;

private:
	UFUNCTION()
	void TurnTimerCompleteCallback();

	FTimerHandle TurnTimer;

public:
	FORCEINLINE APlayerState* GetActivePlayerRef() { return ActivePlayerRef; }

	template< class T >
	T* GetActivePlayerRef() const
	{
		return Cast<T>(ActivePlayerRef);
	}

	FORCEINLINE UTicTacToeBoard* GetBoardRef() { return BoardRef; }

	EBoardCellStatus GetPlayerFlag(int32 PlayerID);

	APlayerState* GetPlayer(int32 PlayerID) const;

private:
	UPROPERTY()
	APlayerState* ActivePlayerRef;

	uint32 ActivePlayerIndex;

	int32 FirstPlayerID;

	UPROPERTY()
	UTicTacToeBoard* BoardRef;
};
