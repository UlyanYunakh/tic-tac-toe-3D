// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameMode.generated.h"

class AChip;

UCLASS()
class TICTACTOE3D_API ATicTacToeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGameBoard();

protected:
	class UTicTacToeBoard* GameBoard;

public:
	UPROPERTY(EditAnywhere, Category = "Class refs")
	TSubclassOf<AChip> ChipClassRef;
	
};
