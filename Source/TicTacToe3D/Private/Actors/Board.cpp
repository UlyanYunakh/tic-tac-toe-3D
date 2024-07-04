// Ullian Yunakh.


#include "Actors/Board.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/Column.h"


ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;

	ColumnMargin = 20.0f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	ColumnsSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Columns"));
	ColumnsSceneComponent->SetupAttachment(RootComponent);

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);
}


void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABoard::OnConstruction(const FTransform& Transform)
{
	UpdateColumnSceneLocation();

	CreateColumns();
}


void ABoard::UpdateColumnSceneLocation()
{
	const float margin = ColumnMargin * 1.5f;

	FVector relativeLocation = ColumnsSceneComponent->GetRelativeLocation();
	relativeLocation.X = -margin;
	relativeLocation.Y = -margin;

	ColumnsSceneComponent->SetRelativeLocation(relativeLocation);
}


void ABoard::CreateColumns()
{
	if (!GetWorld() || !ColumnClassRef) return;

	TArray<AActor*> attachedActors;
	GetAttachedActors(attachedActors, true);

	for (AActor* actor : attachedActors)
	{
		if (AColumn* column = Cast<AColumn>(actor))
		{
			column->Destroy();
		}
	}

	for (uint8 i = 0; i < 16; i++)
	{
		const uint8 rowIndex = i >> 2;
		const uint8 columnIndex = i % 4;
		const FVector relativeLocation = FVector(rowIndex * ColumnMargin, columnIndex * ColumnMargin, 0);

		AColumn* column = GetWorld()->SpawnActor<AColumn>(ColumnClassRef);
		column->AttachToComponent(ColumnsSceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		column->SetActorRelativeLocation(relativeLocation);
	}
}
