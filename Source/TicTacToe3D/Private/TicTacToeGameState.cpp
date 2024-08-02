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


void ATicTacToeGameState::HandleMatchHasStarted()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		BoardRef = NewObject<UTicTacToeBoard>(this); // init board ref
		NonSpectatorPlayers.Empty();
	}
}

void ATicTacToeGameState::SelectFirstActivePlayer()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		ActivePlayerIndex = FMath::RandRange(0, 1);

		UpdateActivePlayerRef();
	}
}

void ATicTacToeGameState::SelectNextActivePlayer()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		ActivePlayerIndex = (ActivePlayerIndex + 1) % 2;

		UpdateActivePlayerRef();
	}
}

void ATicTacToeGameState::UpdateActivePlayerRef()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (NonSpectatorPlayers.IsEmpty())
		{
			InitNonSpectatorPlayersArray();
		}

		if (NonSpectatorPlayers.IsValidIndex(ActivePlayerIndex))
		{
			ActivePlayerRef = NonSpectatorPlayers[ActivePlayerIndex];
			checkf(ActivePlayerRef, TEXT("ActivePlayerRef is nullptr"));

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Server: %s is new active player"), *ActivePlayerRef->GetName()));
		}
	}
}


void ATicTacToeGameState::InitNonSpectatorPlayersArray()
{
	NonSpectatorPlayers = PlayerArray.FilterByPredicate([](const TObjectPtr<APlayerState>& PS) { return !PS.Get()->IsSpectator(); });

	checkf(NonSpectatorPlayers.Num() == 2, TEXT("Incorrect number of players"));
}

// OTHER 

void ATicTacToeGameState::StartTurnCountdown()
{
	if (GetWorld())
	{
		//GetWorldTimerManager().SetTimer(TurnCountdown, this, &ATicTacToeGameState::StartTurn, TurnCountdownTime, false);
	}
}


void ATicTacToeGameState::StartTurnTimer()
{
	if (GetWorld())
	{
		//GetWorldTimerManager().SetTimer(TurnTimer, this, &ATicTacToeGameState::EndTurn, TurnTime, false);
	}
}
