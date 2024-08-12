// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <TicTacToeTypes.h>
#include "Components/TimelineComponent.h"
#include "Column.generated.h"

DECLARE_DELEGATE(FOnAnimationEnded);

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
	void PlacePiace(AChip* SpawnedPiace);

protected:
	virtual void BeginPlay() override;

	virtual bool CanPlaceChip();

public:
	virtual void Tick(float DeltaTime) override;

public:
	FOnAnimationEnded OnAnimationEnded;

protected:
	UFUNCTION()
	void LerpPieceLocation();

	UFUNCTION()
	void EndPieceAnimation();

public:
	void SetID(uint8 ID);
	
	FORCEINLINE int32 GetID() const { return ColumnID; }

protected:
	UPROPERTY(EditAnywhere, Category = "Piace", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* PieceAnimationCurve;

	UPROPERTY(EditAnywhere, Category = "Piace", meta = (AllowPrivateAccess = "true"))
	float PiaeceZOffsetBottom = 10.0f;

private:
	UPROPERTY()
	AChip* AnimatedPiece;

	FVector StartAnimationLocation;
	FVector TargetAnimationLocation;

	FTimeline PieceAnimationTimeline;

protected:
	UPROPERTY()
	TArray<AChip*> Pieces;

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 ColumnID;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ColumnMeshComponent;
};
