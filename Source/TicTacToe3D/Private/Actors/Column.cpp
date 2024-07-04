// Ullian Yunakh.


#include "Actors/Column.h"


AColumn::AColumn()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	ColumnMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ColumnMesh"));
	ColumnMeshComponent->SetupAttachment(RootComponent);
}


void AColumn::BeginPlay()
{
	Super::BeginPlay();

	OnBeginCursorOver.AddDynamic(this, &AColumn::EnableHightlight);
	OnEndCursorOver.AddDynamic(this, &AColumn::DisableHighlight);
}


void AColumn::EnableHightlight(AActor* TouchedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Highlight"));
}


void AColumn::DisableHighlight(AActor* TouchedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Highlight"));
}


void AColumn::AddChip(EBoardCellStatus Player)
{
	
}

