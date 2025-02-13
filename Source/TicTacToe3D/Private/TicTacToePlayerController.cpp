// Ullian Yunakh.


#include "TicTacToePlayerController.h"
#include "TicTacToeTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Column.h"
#include "Actors/Board.h"
#include "TicTacToeGameState.h"
#include "TicTacToeBoard.h"
#include "TicTacToeFunctionLibrary.h"
#include "TicTacToePlayerState.h"


ATicTacToePlayerController::ATicTacToePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
}


void ATicTacToePlayerController::BeginPlay()
{
	Super::BeginPlay();
}


void ATicTacToePlayerController::DoCursorLineTrace()
{
	FHitResult hitResult;
	
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Pointer), false, hitResult);

	if ((!hitResult.bBlockingHit || !hitResult.GetActor()) && ActiveColumn)
	{
		ActiveColumn->DisableHighlight();
		ActiveColumn = nullptr;
		
		return;
	}

	if (AColumn* column = Cast<AColumn>(hitResult.GetActor()))
	{
		if (column != ActiveColumn)
		{
			if (ActiveColumn)
			{
				ActiveColumn->DisableHighlight();
			}

			ActiveColumn = column;
			ActiveColumn->EnableHightlight();
		}
	}
}


void ATicTacToePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoCursorLineTrace();
}


void ATicTacToePlayerController::PlaceChip()
{
	if (!ActiveColumn) return;

	int32 ColumnID = ActiveColumn->GetID();

	int32 PlayerID = -1;
	if (APlayerState* PS = GetPlayerState<APlayerState>())
	{
		PlayerID = PS->GetPlayerId();
	}
	if (PlayerID < 0) return;

	if (ABoard* board = Cast<ABoard>(ActiveColumn->GetAttachParentActor()))
	{
		board->AddPieceToBoard(PlayerID, ColumnID);
	}
}

