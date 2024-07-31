// Ullian Yunakh.


#include "TicTacToePlayerState.h"


void ATicTacToePlayerState::StartTurn()
{
	OnTurnStarted.ExecuteIfBound();
}


void ATicTacToePlayerState::EndTurn()
{
	OnTurnEnded.ExecuteIfBound();
}
