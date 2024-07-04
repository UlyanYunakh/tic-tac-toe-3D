// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class AColumn;

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

private:
	void UpdateColumnSceneLocation();
	void CreateColumns();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAcces = "true"))
	TSubclassOf<AColumn> ColumnClassRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAcces = "true"))
	float ColumnMargin;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "true"))
	USceneComponent* ColumnsSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "true"))
	UStaticMeshComponent* BaseMeshComponent;
};
