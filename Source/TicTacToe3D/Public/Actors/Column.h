// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <TicTacToeTypes.h>
#include "Components/TimelineComponent.h"
#include "Column.generated.h"

class AChip;

UCLASS()
class TICTACTOE3D_API AColumn : public AActor
{
	GENERATED_BODY()
	
public:	
	AColumn();

public:
	virtual void EnableHightlight();
	virtual void DisableHighlight();

public:
	void PlaceChip(EBoardCellStatus Player);

protected:
	virtual void BeginPlay() override;

	virtual bool CanPlaceChip();

public:
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE uint8 GetIndex() { return ColumnIndex; }
	FORCEINLINE void SetIndex(uint8 Index) { ColumnIndex = Index; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ColumnMeshComponent;

protected:
	UFUNCTION()
	void LerpChipLocation();

	UFUNCTION()
	void EndChipAnimation();

	UPROPERTY(EditAnywhere, Category = "Chip", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* ChipSpawnAnimationCurve;

	UPROPERTY(EditAnywhere, Category = "Chip", meta = (AllowPrivateAccess = "true"))
	float SpawnZOffsetMax = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Chip", meta = (AllowPrivateAccess = "true"))
	float SpawnZOffsetMin = 10.0f;

	UPROPERTY()
	AChip* ActiveChip;

	FVector StartLocation;
	FVector TargetLocation;

	FTimeline ChipTimeline;

protected:
	UPROPERTY()
	TArray<AChip*> Chips;

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	uint8 ColumnIndex;
};
