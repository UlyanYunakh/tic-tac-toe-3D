// Ullian Yunakh.


#include "TicTacToeGameState.h"
#include "TicTacToeBoard.h"
#include "GameFramework/PlayerState.h"
#include "TicTacToePlayerState.h"

ATicTacToeGameState::ATicTacToeGameState()
{
	TurnCountdownTime = 3.0f;
	TurnTime = 10.0f;
}

void ATicTacToeGameState::HandleMatchIsWaitingToStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Mathc: waiting to start"));
	BoardRef = NewObject<UTicTacToeBoard>(this);
}

void ATicTacToeGameState::HandleMatchHasStarted()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Mathc: waiting started"));
	
	// check(PlayerArray.Num() > 1, TEXT("Game started with incorrect amount of players"));

	// ActivePlayerID = SelectFirstPlayer();
}


uint32 ATicTacToeGameState::SelectFirstPlayer()
{
	uint32 FirstPlayerID;

	if (ATicTacToePlayerState* Player_1 = Cast<ATicTacToePlayerState>(PlayerArray[0]))
	{
		Player_1->SetPlayerFlag(EBoardCellStatus::Player_1);
		FirstPlayerID = Player_1->GetPlayerId();
	}

	if (ATicTacToePlayerState* Player_2 = Cast<ATicTacToePlayerState>(PlayerArray[0]))
	{
		Player_2->SetPlayerFlag(EBoardCellStatus::Player_2);
	}

	return FirstPlayerID;
}


uint32 ATicTacToeGameState::SelectNextPlayer()
{
	int32 currID = ActivePlayerID;
	TObjectPtr<APlayerState>* nextPlayer = PlayerArray.FindByPredicate([&currID](const TObjectPtr<APlayerState>& PS) { return PS.Get()->GetPlayerId() != currID; });
	
	return nextPlayer->Get()->GetPlayerId();
}


void ATicTacToeGameState::InitiateTurnForPlayer(uint32 PlayerID)
{
	ActivePlayerID = PlayerID;

	StartTurnCountdown();
}

void ATicTacToeGameState::StartTurn()
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TurnCountdown);
	}

	StartTurnTimer();
}

void ATicTacToeGameState::EndTurn()
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TurnTimer);
	}

	ActivePlayerID = SelectNextPlayer();
}

void ATicTacToeGameState::StartTurnCountdown()
{
	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(TurnCountdown, this, &ATicTacToeGameState::StartTurn, TurnCountdownTime, false);
	}
}

void ATicTacToeGameState::StartTurnTimer()
{
	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(TurnTimer, this, &ATicTacToeGameState::EndTurn, TurnTime, false);
	}
}
