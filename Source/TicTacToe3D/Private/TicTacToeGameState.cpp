// Ullian Yunakh.


#include "TicTacToeGameState.h"
#include "TicTacToeBoard.h"
#include "GameFramework/PlayerState.h"
#include "TicTacToePlayerState.h"

ATicTacToeGameState::ATicTacToeGameState()
{
	
}


void ATicTacToeGameState::HandleMatchHasStarted()
{
	BoardRef = NewObject<UTicTacToeBoard>(this); // init board ref
	NonSpectatorPlayers.Empty();
}

void ATicTacToeGameState::SelectFirstActivePlayer()
{
	InitNonSpectatorPlayersArray();

	for (int32 i = 0; i < NonSpectatorPlayers.Num(); i++)
	{
		if (!NonSpectatorPlayers[i]->IsABot())
		{
			ActivePlayerIndex = i;
			break;
		}
	}

	UpdateActivePlayerRef();
}

void ATicTacToeGameState::SelectNextActivePlayer()
{
	//ActivePlayerIndex = (ActivePlayerIndex + 1) % 2;

	UpdateActivePlayerRef();
}

void ATicTacToeGameState::UpdateActivePlayerRef()
{
	if (NonSpectatorPlayers.IsEmpty())
	{
		InitNonSpectatorPlayersArray();
	}

	if (NonSpectatorPlayers.IsValidIndex(ActivePlayerIndex))
	{
		ActivePlayerRef = NonSpectatorPlayers[ActivePlayerIndex];
		checkf(ActivePlayerRef, TEXT("ActivePlayerRef is nullptr"));

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("GAME: %s is new active player"), *ActivePlayerRef->GetPlayerName()));
	}
}


void ATicTacToeGameState::InitNonSpectatorPlayersArray()
{
	NonSpectatorPlayers = PlayerArray.FilterByPredicate([](const TObjectPtr<APlayerState>& PS) { return !PS.Get()->IsSpectator(); });

	checkf(NonSpectatorPlayers.Num() == 2, TEXT("Incorrect number of players"));
}


void ATicTacToeGameState::StartTurnTimer(const float TurnDuration)
{
	if (GetWorld())
	{
		FTimerDynamicDelegate turnDelegate;
		turnDelegate.BindUFunction(this, TEXT("TurnTimerCompleteCallback"));
		
		GetWorldTimerManager().SetTimer(TurnTimer, turnDelegate, TurnDuration, false);
	}
}


void ATicTacToeGameState::ClearTurnTimer()
{
	if (GetWorld())
	{
		OnTurnTimerEnd.Unbind();
		GetWorldTimerManager().ClearTimer(TurnTimer);
	}
}


void ATicTacToeGameState::TurnTimerCompleteCallback()
{
	if (OnTurnTimerEnd.IsBound()) // unbind function is unchecked (if not bound app will crash)
	{
		OnTurnTimerEnd.Execute(ActivePlayerRef);
		OnTurnTimerEnd.Unbind();
	}
}


EBoardCellStatus ATicTacToeGameState::GetPlayerFlag(int32 PlayerID)
{
	return PlayerID == FirstPlayerID ? EBoardCellStatus::Player_1 : EBoardCellStatus::Player_2;
}


APlayerState* ATicTacToeGameState::GetPlayer(int32 PlayerID) const
{
	auto IsPlayerIDEqual = [&PlayerID](const TObjectPtr<APlayerState>& PS) { return PS.Get()->GetPlayerId() == PlayerID; };

	const TObjectPtr<APlayerState>* player = PlayerArray.FindByPredicate(IsPlayerIDEqual);

	return (*player);
}
