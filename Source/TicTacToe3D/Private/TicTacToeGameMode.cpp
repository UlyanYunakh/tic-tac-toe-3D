// Ullian Yunakh.


#include "TicTacToeGameMode.h"
#include <TicTacToeBoard.h>
#include "Actors/Chip.h"
#include "TicTacToeGameState.h"
#include "GameFramework/PlayerState.h"


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
		GetWorldTimerManager().SetTimer(InitialDelayTimer, this, &ATicTacToeGameMode::FirstpreTurnStart, InitialDelayTime, false);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Server: match has started"));
}


void ATicTacToeGameMode::FirstpreTurnStart()
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
	if (ATicTacToeGameState* TTT_GS = GetGameState<ATicTacToeGameState>())
	{
		APlayerState* PS = TTT_GS->GetActivePlayerRef();
		checkf(PS, TEXT("Ref is nullptr"));

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Server: turn started for %s"), *PS->GetName()));
	}
}

void ATicTacToeGameMode::EndTurn()
{
}

