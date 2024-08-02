// Ullian Yunakh.


#include "TicTacToePlayerState.h"


void ATicTacToePlayerState::StartTurn_Implementation()
{
	OnTurnStarted.ExecuteIfBound();
}


void ATicTacToePlayerState::EndTurn_Implementation()
{
	OnTurnEnded.ExecuteIfBound();
}
