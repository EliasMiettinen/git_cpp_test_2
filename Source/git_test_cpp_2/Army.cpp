#include "Army.h"

// Constructor
AArmy::AArmy()
{
	// Set up a root component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
	
	SelectionMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionMarker"));
	SelectionMarker->SetupAttachment(RootComponent);
	SelectionMarker->SetVisibility(false);
	SelectionMarker->SetCollisionProfileName(TEXT("NoCollision"));
	
	// Components
	Navigator = CreateDefaultSubobject<UArmyNavigator>(TEXT("Navigator"));
	Movement = CreateDefaultSubobject<UArmyMovementComponent>(TEXT("Movement"));
	
	// Initialize properties
	OwnerId = -1;
	Tile = nullptr;
	bIsSelected = false;
	MovementPoints = 0;
	CurrentPreviewUnitIndex = -1;
	PreviewUnit = nullptr;
}

void AArmy::BeginPlay()
{
	Super::BeginPlay();
}

void AArmy::Select()
{
	bIsSelected = true;
	SelectionMarker->SetVisibility(true);
	
}

void AArmy::Deselect()
{
	bIsSelected = false;
	SelectionMarker->SetVisibility(false);
}

/**
 * Add unit to the army
 * @param Unit 
 */
void AArmy::AddUnit(FUnit Unit)
{
	Units.Add(Unit);
	Movement->CalculateMovementPoints();
	
	// TODO: DEPRECATED, ONLY FOR DEVELOPMENT PURPOSES, NEED ACTUAL LOGIC TO SELECT THE PREVIEW UNIT
	UpdatePreviewUnit(Units.Num() - 1);
}

/**
 * Remove the unit from the index
 * @param Index 
 */
void AArmy::RemoveUnit(int32 Index)
{
	if (Index < 0 || Index >= Units.Num()) return;
	
	Units.RemoveAt(Index);
}

/**
 * Update the army's tile reference
 * @param NewTile 
 */
void AArmy::UpdateTile(ATile* NewTile)
{
	if (NewTile == nullptr) return;
	
	if (Tile)
	{
		Tile->Army = nullptr;
	}
	Tile = NewTile;
	Tile->Army = this;
}

void AArmy::UpdatePreviewUnit(int32 Index)
{
	if (CurrentPreviewUnitIndex == Index) return;
	if (Index < 0 || Index >= Units.Num()) return;
	
	FUnit& Unit = Units[Index];
	CurrentPreviewUnitIndex = Index;
	
	// Remove previous preview unit
	if (PreviewUnit) PreviewUnit->Destroy();
	
	// Spawn new preview unit
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	PreviewUnit = GetWorld()->SpawnActor<AUnitPreview>(Unit.PreviewClass, SpawnLocation, SpawnRotation);
	if (!PreviewUnit) return;
	PreviewUnit->SetOwner(this);
	PreviewUnit->AttachToComponent(Root, FAttachmentTransformRules::KeepWorldTransform);
}

#pragma region Actions

void AArmy::Move(ATile* TargetTile)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Moving army COMMAND IN ARMY.CPP")));
	if (Movement == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Movement component is null for army %s"), *GetName()));
		return;
	}
	if (Movement == nullptr || TargetTile == nullptr) return;
	
	// Move the army
	Movement->Move(TargetTile);
}

#pragma endregion
