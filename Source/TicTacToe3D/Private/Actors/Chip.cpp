// Ullian Yunakh.


#include "Actors/Chip.h"
#include "Net/UnrealNetwork.h"


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


void AChip::SetMeshMaterialByPlayer(EBoardCellStatus PlayerFlag)
{
	Owner = PlayerFlag;

	UMaterialInterface* parentMaterial = Owner == EBoardCellStatus::Player_1 ? MeshMaterial_P1 : MeshMaterial_P2;
	UMaterialInstanceDynamic* newMaterialInst = UMaterialInstanceDynamic::Create(parentMaterial, this);

	if (newMaterialInst && ChipMeshComponent)
	{
		ChipMeshComponent->SetMaterial(0, newMaterialInst);
	}
}


float AChip::GetChipHeight()
{
	return ChipMeshComponent->Bounds.BoxExtent.Z * 2; // * 2 because origin is in the center of a mesh
}

