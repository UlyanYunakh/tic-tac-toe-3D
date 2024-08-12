// Ullian Yunakh.


#include "TicTacToeGameMode.h"
#include <TicTacToeBoard.h>
#include "Actors/Chip.h"
#include "TicTacToeGameState.h"
#include "TicTacToePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Board.h"


void ATicTacToeGameMode::HandleMatchIsWaitingToStart()
{

}


bool ATicTacToeGameMode::ReadyToStartMatch_Implementation()
{
	return GetGameState<AGameState>()->PlayerArray.Num() == 2; // start match only if two players connected
}


void ATicTacToeGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(InitialDelayTimer, this, &ATicTacToeGameMode::FirstPreTurnStart, InitialDelayTime, false);
	}
}


void ATicTacToeGameMode::FirstPreTurnStart()
{
	if (ATicTacToeGameState* TTT_GS = GetGameState<ATicTacToeGameState>())
	{
		TTT_GS->SelectFirstActivePlayer();

		StartTurn();
	}
}


void ATicTacToeGameMode::PreTurnStart()
{
	if (ATicTacToeGameState* TTT_GS = GetGameState<ATicTacToeGameState>())
	{
		TTT_GS->SelectNextActivePlayer();

		StartTurn();
	}
}

void ATicTacToeGameMode::StartTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("GAME: Turn started"));

	if (ATicTacToeGameState* TTT_GS = GetGameState<ATicTacToeGameState>())
	{
		TTT_GS->OnTurnTimerEnd.BindUObject(this, &ATicTacToeGameMode::TurnTimerEnd);
		TTT_GS->StartTurnTimer(TurnDuration);

		if (ATicTacToePlayerState* TTT_PS = TTT_GS->GetActivePlayerRef<ATicTacToePlayerState>())
		{
			TTT_PS->SetMovePermision(true);
		}
	}
}


void ATicTacToeGameMode::PlayerMadeMove(int32 PlayerID, TDelegate<void()>& PieceAddedDelegate)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("GAME: Player made his move"));

	if (ATicTacToeGameState* TTT_GS = GetGameState<ATicTacToeGameState>())
	{
		ATicTacToePlayerState* TTT_PS = TTT_GS->GetActivePlayerRef<ATicTacToePlayerState>();

		if (!TTT_PS || TTT_PS->GetPlayerId() != PlayerID) return;

		TTT_PS->SetMovePermision(false);
		TTT_GS->ClearTurnTimer();
	}
	
	PieceAddedDelegate.BindUObject(this, &ATicTacToeGameMode::EndTurn);
}


void ATicTacToeGameMode::EndTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("GAME: Player's turn ended"));

	PreTurnStart();
}


void ATicTacToeGameMode::TurnTimerEnd(APlayerState* PlayerStateRef)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("GAME: Turn timer ended"));
	EndTurn();
}

