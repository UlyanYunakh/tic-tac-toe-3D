// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacToeTypes.h"
#include "Board.generated.h"

DECLARE_DELEGATE(FOnPieceAdded);

class AColumn;
class AChip;
class UTicTacToeBoard;

UCLASS()
class TICTACTOE3D_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:
	ABoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Destroyed() override;

	void AddPieceToBoard(int32 PlayerID, int32 ColumnID);

private:
	void SpawnPiece(EBoardCellStatus PlayerFlag, int32 ColumnID);
	void PieceAdded();

private:
	void UpdateColumnSceneLocation();
	void CreateColumns();
	void DestroyColumns();

private:
	FOnPieceAdded OnPieceAdded;

private:
	UPROPERTY()
	UTicTacToeBoard* BoardGameModelRef;

	UPROPERTY()
	TArray<AColumn*> Columns;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAcces = "true"))
	TSubclassOf<AColumn> ColumnClassRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAcces = "true"))
	TSubclassOf<AChip> PieaceClassRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAcces = "true"))
	float ColumnsMargin = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Chip", meta = (AllowPrivateAccess = "true"))
	float PieaceSpawnZOffset = 100.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "true"))
	USceneComponent* ColumnsSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "true"))
	UStaticMeshComponent* BaseMeshComponent;
};
