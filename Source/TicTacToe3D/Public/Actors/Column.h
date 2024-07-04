// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <TicTacToeTypes.h>
#include "Column.generated.h"

UCLASS()
class TICTACTOE3D_API AColumn : public AActor
{
	GENERATED_BODY()
	
public:	
	AColumn();

protected:
	virtual void BeginPlay() override;

	virtual void EnableHightlight(AActor* TouchedActor);
	virtual void DisableHighlight(AActor* TouchedActor);

	UFUNCTION(BlueprintCallable)
	void AddChip(EBoardCellStatus Player);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* ColumnMeshComponent;

protected:
	uint8 ColumnIndex;

};
