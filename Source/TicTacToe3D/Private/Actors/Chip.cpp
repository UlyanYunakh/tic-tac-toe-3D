// Ullian Yunakh.


#include "Actors/Chip.h"


AChip::AChip()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	ChipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChipMesh"));
	ChipMeshComponent->SetupAttachment(RootComponent);
	ChipMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AChip::BeginPlay()
{
	Super::BeginPlay();
}


void AChip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AChip::GetChipHeight()
{
	return ChipMeshComponent->Bounds.BoxExtent.Z * 2; // * 2 because origin is in the center of a mesh
}

