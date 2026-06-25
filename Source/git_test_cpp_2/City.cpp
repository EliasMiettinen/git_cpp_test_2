// Fill out your copyright notice in the Description page of Project Settings.


#include "City.h"


// Sets default values
ACity::ACity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	Name = "Unnamed City";
	OwnerPlayer = -1;
	Tile = nullptr;
}

// Called when the game starts or when spawned
void ACity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACity::Initialize(ATile* InTile, int32 InOwner, FString InName)
{
	Tile = InTile;
	OwnerPlayer = InOwner;
	Name = InName;
}

void ACity::SpawnUnit(UUnitData* InUnit)
{
	FUnit Unit = ConvertUnitDataToUnit(InUnit);
	
	AArmy* AsArmy = GetArmy();
	AsArmy->AddUnit(Unit);
}

/**
 * Retrieves the army associated with the city. If the army is not already present,
 * a new one is spawned at the tile's location, initialized with the city's owner and tile,
 * and associated with the tile and the city.
 *
 * @return A pointer to the AArmy instance associated with the city. Returns nullptr if the army could not be spawned.
 */
AArmy* ACity::GetArmy()
{
	if (Army == nullptr)
	{
		FVector SpawnLocation = Tile->GetTargetPointLocation();
		AArmy* NewArmy = GetWorld()->SpawnActor<AArmy>(ArmyClass, SpawnLocation, FRotator::ZeroRotator);
		
		NewArmy->UpdateTile(Tile);
		NewArmy->OwnerId = OwnerPlayer;
		Tile->Army = NewArmy;
		
		Army = NewArmy;
	}
	
	return Army;
}

FUnit ACity::ConvertUnitDataToUnit(UUnitData* InUnitData)
{
	FUnit Unit;
	Unit.Name = InUnitData->DisplayName;
	Unit.Health = InUnitData->MaxHealth;
	Unit.MaxHealth = InUnitData->MaxHealth;
	Unit.MaxMovementPoints = InUnitData->MaxMovementPoints;
	Unit.MovementPoints = InUnitData->MaxMovementPoints;
	Unit.AttackDamage = InUnitData->AttackDamage;
	Unit.Armor = InUnitData->Armor;
	Unit.Strength = InUnitData->Strength;
	Unit.Icon = InUnitData->Icon;
	Unit.PreviewClass = InUnitData->PreviewClass;
	
	return Unit;
}


