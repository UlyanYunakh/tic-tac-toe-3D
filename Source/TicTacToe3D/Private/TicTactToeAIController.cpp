// Ullian Yunakh.


#include "TicTactToeAIController.h"
#include "TicTacToeBoard.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Board.h"
#include "TicTacToeFunctionLibrary.h"
#include "GameFramework/PlayerState.h"
#include "TicTacToePlayerState.h"


void ATicTactToeAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ATicTacToePlayerState* TTT_PS = GetPlayerState<ATicTacToePlayerState>())
	{
		TTT_PS->OnPermissionChanged.BindUObject(this, &ATicTactToeAIController::PermissionChanged);
	}
}


void ATicTactToeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMakingMove && MinimaxPayloadFuture.IsReady())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("row %d, column %d, layer %d"), MinimaxPayloadFuture.Get().BestMove.Row, MinimaxPayloadFuture.Get().BestMove.Column, MinimaxPayloadFuture.Get().BestMove.Layer));

		int32 ColumnID = GetColumnID(MinimaxPayloadFuture.Get().BestMove);

		MakeAMove(ColumnID);

		bMakingMove = false;

		MinimaxPayloadFuture.Reset();
	}
}


void ATicTactToeAIController::PermissionChanged(bool Permission)
{
	bMakingMove = Permission;

	if (bMakingMove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("AI: Starting turn"));

		FindBestMove();
	}
}


void ATicTactToeAIController::FindBestMove()
{
	GetCopyOfGameBoardModel();

	/*TPromise<int> Promise;
	MinimaxPayloadFuture = Promise.GetFuture();*/

	UTicTacToeBoard* GameBoardModelCopy = GameBoardModelCopyRef;
	int32 d = MinimaxDeapth;

	MinimaxPayloadFuture = Async(EAsyncExecution::Thread, [GameBoardModelCopy, &d]() {
		FMinimaxPayload payload;
		payload.Board = GameBoardModelCopy;
		payload.MaxDepth = d;
		payload.MaximizingPlayer = EBoardCellStatus::Player_2;
		payload.MinimizingPlayer = EBoardCellStatus::Player_1;

		UTicTacToeFunctionLibrary::Minimax(payload, 0, true, -INFINITY, INFINITY);

		FTimerHandle handle;
		FTimerDelegate delegate;

		return payload;

		//Promise.SetValue(payload);

		/*delegate.BindLambda([&]() {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("DELEGATE CALLED"));

		});

		GetWorldTimerManager().SetTimer(handle, delegate, 5.0f, false);*/
		
	});
}


void ATicTactToeAIController::MakeAMove(int32 ColumnID)
{
	ABoard* boardRef = nullptr;
	if (GetWorld())
	{
		boardRef = Cast<ABoard>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoard::StaticClass()));
	}
	if (!boardRef) return;

	int32 PlayerID = -1;
	if (APlayerState* PS = GetPlayerState<APlayerState>())
	{
		PlayerID = PS->GetPlayerId();
	}
	if (PlayerID < 0) return;

	boardRef->AddPieceToBoard(PlayerID, ColumnID);
}


void ATicTactToeAIController::GetCopyOfGameBoardModel()
{
	ABoard* boardRef = nullptr;
	if (GetWorld())
	{
		boardRef = Cast<ABoard>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoard::StaticClass()));
	}
	if (!boardRef) return;

	GameBoardModelCopyRef = DuplicateObject(boardRef->GetGameBoardModel(), this);
}


int32 ATicTactToeAIController::GetColumnID(FBoardCellLocation Location)
{
	return Location.Row * 4 + Location.Column;
}
