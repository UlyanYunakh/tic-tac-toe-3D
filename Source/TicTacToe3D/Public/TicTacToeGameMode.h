// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TicTacToeGameMode.generated.h"

class AChip;

UCLASS()
class TICTACTOE3D_API ATicTacToeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Class refs")
	TSubclassOf<AChip> ChipClassRef;
	
};
