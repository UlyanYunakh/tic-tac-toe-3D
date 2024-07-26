// Ullian Yunakh.


#include "TicTacToePlayerController.h"
#include "TicTacToeTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Column.h"


ATicTacToePlayerController::ATicTacToePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
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

	ActiveColumn->PlaceChip(EBoardCellStatus::Player_1);
}
