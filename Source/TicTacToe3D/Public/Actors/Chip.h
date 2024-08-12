// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacToeTypes.h"
#include "Chip.generated.h"

UCLASS()
class TICTACTOE3D_API AChip : public AActor
{
	GENERATED_BODY()
	
public:
	AChip();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetMeshMaterialByPlayer(EBoardCellStatus PlayerFlag);

	float GetChipHeight();

private:
	EBoardCellStatus Owner;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* MeshMaterial_P1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* MeshMaterial_P2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ChipMeshComponent;
};
