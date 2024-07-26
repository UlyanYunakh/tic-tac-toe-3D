// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	float GetChipHeight();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ChipMeshComponent;
};
