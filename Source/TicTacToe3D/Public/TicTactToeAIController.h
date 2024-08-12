// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TicTacToeTypes.h"
#include "TicTactToeAIController.generated.h"

class UTicTacToeBoard;

UCLASS()
class TICTACTOE3D_API ATicTactToeAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	UFUNCTION()
	void PermissionChanged(bool Permission);

	void FindBestMove();

	void MakeAMove(int32 ColumnID);

private:
	void GetCopyOfGameBoardModel();
	int32 GetColumnID(FBoardCellLocation Location);

private:
	bool bMakingMove;
	int32 MinimaxDeapth = 3;

	UPROPERTY()
	UTicTacToeBoard* GameBoardModelCopyRef;

	TFuture<FMinimaxPayload> MinimaxPayloadFuture;
};
