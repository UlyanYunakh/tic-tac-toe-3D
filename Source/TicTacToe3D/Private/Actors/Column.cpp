// Ullian Yunakh.


#include "Actors/Column.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Chip.h"
#include "TicTacToeGameMode.h"
#include "Net/UnrealNetwork.h"


AColumn::AColumn()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	ColumnMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ColumnMesh"));
	ColumnMeshComponent->SetupAttachment(RootComponent);
	ColumnMeshComponent->SetCustomDepthStencilValue(1);
	ColumnMeshComponent->SetCollisionResponseToChannel(ECC_Pointer, ECR_Block);
}


void AColumn::BeginPlay()
{
	Super::BeginPlay();

	if (PieceAnimationCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("LerpPieceLocation"));
		TimelineFinishedCallback.BindUFunction(this, FName("EndPieceAnimation"));
		PieceAnimationTimeline.AddInterpFloat(PieceAnimationCurve, TimelineCallback);
		PieceAnimationTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);

		PieceAnimationTimeline.Stop();
	}
}


void AColumn::EnableHightlight()
{
	ColumnMeshComponent->SetRenderCustomDepth(true);
}


void AColumn::DisableHighlight()
{
	ColumnMeshComponent->SetRenderCustomDepth(false);
}


void AColumn::PlacePiace(AChip* SpawnedPiace)
{
	StartAnimationLocation = SpawnedPiace->GetActorLocation();
	TargetAnimationLocation = GetActorLocation() + FVector::ZAxisVector * SpawnedPiace->GetChipHeight() * Pieces.Num() + FVector::ZAxisVector * PiaeceZOffsetBottom;

	Pieces.Add(SpawnedPiace);

	AnimatedPiece = SpawnedPiace;

	PieceAnimationTimeline.PlayFromStart();
}


bool AColumn::CanPlaceChip()
{
	return Pieces.Num() < 4 && !PieceAnimationTimeline.IsPlaying();
}


void AColumn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PieceAnimationTimeline.TickTimeline(DeltaTime);
}


void AColumn::LerpPieceLocation()
{
	if (!AnimatedPiece) return;

	float timelineValue = PieceAnimationTimeline.GetPlaybackPosition();
	float alpha = PieceAnimationCurve->GetFloatValue(timelineValue);;
	FVector newLocation = FMath::Lerp(StartAnimationLocation, TargetAnimationLocation, alpha);

	AnimatedPiece->SetActorLocation(newLocation);
}


void AColumn::EndPieceAnimation()
{
	if (!AnimatedPiece) return;

	AnimatedPiece->SetActorLocation(TargetAnimationLocation);
	AnimatedPiece = nullptr;

	PieceAnimationTimeline.Stop();

	OnAnimationEnded.ExecuteIfBound();
}


void AColumn::SetID(uint8 ID)
{
	ColumnID = ID;
}