// Ullian Yunakh.


#include "Actors/Column.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Chip.h"
#include "TicTacToeGameMode.h"


AColumn::AColumn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	ColumnMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ColumnMesh"));
	ColumnMeshComponent->SetupAttachment(RootComponent);
	ColumnMeshComponent->SetCustomDepthStencilValue(1);
	ColumnMeshComponent->SetCollisionResponseToChannel(ECC_Pointer, ECR_Block);
}


void AColumn::BeginPlay()
{
	Super::BeginPlay();

	if (ChipSpawnAnimationCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("LerpChipLocation"));
		TimelineFinishedCallback.BindUFunction(this, FName("EndChipAnimation"));
		ChipTimeline.AddInterpFloat(ChipSpawnAnimationCurve, TimelineCallback);
		ChipTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);

		ChipTimeline.Stop();
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


void AColumn::PlaceChip(EBoardCellStatus Player)
{
	if (CanPlaceChip())
	{
		UClass* chipClassRef = GetWorld()->GetAuthGameMode<ATicTacToeGameMode>()->ChipClassRef;

		FTransform spawnTransform;
		spawnTransform.SetLocation(GetActorLocation() + FVector::ZAxisVector * SpawnZOffsetMax);

		ActiveChip = GetWorld()->SpawnActor<AChip>(chipClassRef, spawnTransform);

		StartLocation = ActiveChip->GetActorLocation();
		TargetLocation = GetActorLocation() + FVector::ZAxisVector * ActiveChip->GetChipHeight() * Chips.Num() + FVector::ZAxisVector * SpawnZOffsetMin;

		Chips.Add(ActiveChip);

		ChipTimeline.PlayFromStart();
	}
}


bool AColumn::CanPlaceChip()
{
	return Chips.Num() < 4 && !ChipTimeline.IsPlaying();
}


void AColumn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChipTimeline.TickTimeline(DeltaTime);
}


void AColumn::LerpChipLocation()
{
	if (!ActiveChip) return;

	float timelineValue = ChipTimeline.GetPlaybackPosition();
	float alpha = ChipSpawnAnimationCurve->GetFloatValue(timelineValue);;
	FVector newLocation = FMath::Lerp(StartLocation, TargetLocation, alpha);

	ActiveChip->SetActorLocation(newLocation);
}


void AColumn::EndChipAnimation()
{
	if (ActiveChip) return;

	ActiveChip->SetActorLocation(TargetLocation);
	ActiveChip = nullptr;

	ChipTimeline.Stop();
}

