// Ullian Yunakh.


#include "Actors/Board.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/Column.h"
#include "Actors/Chip.h"
#include "TicTacToeBoard.h"
#include "TicTacToePlayerState.h"
#include "TicTacToeFunctionLibrary.h"
#include "TicTacToeGameMode.h"
#include "TicTacToeGameState.h"


ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	ColumnsSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Columns"));
	ColumnsSceneComponent->SetupAttachment(RootComponent);

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);
}


void ABoard::BeginPlay()
{
	Super::BeginPlay();

	BoardGameModelRef = NewObject<UTicTacToeBoard>(this);
}


void ABoard::OnConstruction(const FTransform& Transform)
{
	UpdateColumnSceneLocation();

	CreateColumns();
}


void ABoard::Destroyed()
{
	/* Destroy attached actors (Columns) */

	DestroyColumns();

	Super::Destroyed();
}


void ABoard::AddPieceToBoard(int32 PlayerID, int32 ColumnID)
{
	if (PlayerID < 0 || ColumnID < 0) return;

	ATicTacToeGameMode* TTT_GM = GetWorld()->GetAuthGameMode<ATicTacToeGameMode>();
	if (!TTT_GM) return;

	ATicTacToeGameState* TTT_GS = TTT_GM->GetGameState<ATicTacToeGameState>();
	if (!TTT_GS) return;

	ATicTacToePlayerState* TTT_PS = Cast<ATicTacToePlayerState>(TTT_GS->GetPlayer(PlayerID));
	if (!TTT_PS) return;

	bool bMovePermission = TTT_PS->GetMovePermission();
	if (!bMovePermission) return;

	EBoardCellStatus playerFlag = TTT_GS->GetPlayerFlag(PlayerID);
	FBoardCellLocation moveLocation = UTicTacToeFunctionLibrary::GetCellLocationByColumnID(BoardGameModelRef, ColumnID);
	BoardGameModelRef->BoardMove(playerFlag, moveLocation);

	TTT_GM->PlayerMadeMove(PlayerID, OnPieceAdded);

	SpawnPiece(playerFlag, ColumnID);
}


void ABoard::SpawnPiece(EBoardCellStatus PlayerFlag, int32 ColumnID)
{
	if (!GetWorld()) return;

	AColumn* spawnColumn = nullptr;
	if (AColumn** column = Columns.FindByPredicate([&ColumnID](const AColumn* C) { return C->GetID() == ColumnID; }))
	{
		spawnColumn = *column;
	}
	if (!spawnColumn) return;

	FTransform spawnTransform;
	spawnTransform.SetLocation(spawnColumn->GetActorLocation() + FVector::ZAxisVector * PieaceSpawnZOffset);

	AChip* spawnedPiece = GetWorld()->SpawnActor<AChip>(PieaceClassRef, spawnTransform);
	spawnedPiece->SetMeshMaterialByPlayer(PlayerFlag);

	spawnColumn->OnAnimationEnded.BindUObject(this, &ABoard::PieceAdded);
	spawnColumn->PlacePiace(spawnedPiece); // will start piece sliding animation 
}


void ABoard::PieceAdded()
{
	if (OnPieceAdded.IsBound()) // unbind function is unchecked (if not bound app will crash)
	{
		OnPieceAdded.Execute();
		OnPieceAdded.Unbind();
	}
}


void ABoard::UpdateColumnSceneLocation()
{
	const float margin = ColumnsMargin * 1.5f;

	FVector relativeLocation = ColumnsSceneComponent->GetRelativeLocation();
	relativeLocation.X = -margin;
	relativeLocation.Y = -margin;

	ColumnsSceneComponent->SetRelativeLocation(relativeLocation);
}


void ABoard::CreateColumns()
{
	if (!GetWorld() || !ColumnClassRef) return;

	DestroyColumns();

	for (uint8 i = 0; i < 16; i++)
	{
		const uint8 rowIndex = i >> 2;
		const uint8 columnIndex = i % 4;
		const FVector relativeLocation = FVector(rowIndex * ColumnsMargin, columnIndex * ColumnsMargin, 0);

		AColumn* column = GetWorld()->SpawnActor<AColumn>(ColumnClassRef);
		column->AttachToComponent(ColumnsSceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		column->SetActorRelativeLocation(relativeLocation);
		column->SetID(i);

		Columns.Add(column);
	}
}


void ABoard::DestroyColumns()
{
	for (AColumn* column : Columns)
	{
		column->Destroy();
	}

	Columns.Empty();
}