// Ullian Yunakh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TicTacToeTypes.h"
#include "TicTacToePlayerState.generated.h"

UCLASS()
class TICTACTOE3D_API ATicTacToePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void SetMovePermision(bool bPermission);

	FORCEINLINE bool GetMovePermission() { return bMovePermission; }

private:
	UPROPERTY(BlueprintReadOnly, Category="MovePermision", meta = (AllowPrivateAccess = "true"))
	bool bMovePermission;
};
