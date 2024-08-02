// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TicTacToeGameMode.generated.h"

class AChip;
class ATicTacToeGameState;

UCLASS()
class TICTACTOE3D_API ATicTacToeGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void HandleMatchIsWaitingToStart() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	
	virtual void HandleMatchHasStarted() override;

	virtual void FirstpreTurnStart();

	virtual void PreTurnStart();

	virtual void StartTurn();

	virtual void EndTurn();

public:
	/* Time before match actually starts */
	UPROPERTY(EditAnywhere, Category="Timers")
	float InitialDelayTime;
	FTimerHandle InitialDelayTimer;

	/* Time between turns */
	UPROPERTY(EditAnywhere, Category = "Timers")
	float BetweenTurnsTime;
	FTimerHandle BetweenTurnsTimer;

	UPROPERTY(EditAnywhere, Category = "Class refs")
	TSubclassOf<AChip> ChipClassRef;
	
};
