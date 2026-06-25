#include "ArmyMovementComponent.h"
#include "Army.h"

// Sets default values for this component's properties
UArmyMovementComponent::UArmyMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	Army = Cast<AArmy>(GetOwner());
}

// Called when component is activated and registered in the parent actor
void UArmyMovementComponent::OnRegister()
{
	Super::OnRegister();
	
	Navigator = Cast<UArmyNavigator>(GetOwner()->GetComponentByClass(UArmyNavigator::StaticClass()));
	if (!Navigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("Army Movement Component registered"));
	}
}

// Called when the game starts
void UArmyMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UArmyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!IsMoving() || Path.Num() == 0) return;
	
	float Distance = FVector::Distance(Army->GetActorLocation(), CurrentTarget->GetTargetPointLocation());
	
	// Rotation logic
	if (Distance > DistanceThreshold)
	{
		// Calculate the rotation
		FVector Direction = (CurrentTarget->GetTargetPointLocation() - Army->GetActorLocation()).GetSafeNormal();
		Direction.Z = 0.0f;
		FRotator TargetRot = Direction.Rotation();
		
		// Smoothly Turn
		FRotator NewRot = FMath::RInterpTo(Army->GetActorRotation(), TargetRot, DeltaTime, RotationSpeed * DeltaTime);
		Army->SetActorRotation(NewRot);
	}
	
	// Movement logic
	if (Distance <= DistanceThreshold)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Army %s reached target %s"), *Army->GetName(), *CurrentTarget->GetName()));
		
		Army->SetActorLocation(CurrentTarget->GetTargetPointLocation());
		Army->UpdateTile(CurrentTarget);
		
		// Get the next target and reduce movement points
		Path.RemoveAt(0);
		MovementPoints--;
		
		if (Path.Num() == 0)
		{
			// Finish the path
			bMoving = false;
			CurrentTarget = nullptr;
		}
		else
		{
			CurrentTarget = Path[0];
			
			// If there are no movement points left, stop and wait for the next turn
			if (MovementPoints <= 0)
			{
				bMoving = false;
			}
		}
	}
	else
	{
		// The movement logic
		FVector Direction = (CurrentTarget->GetTargetPointLocation() - Army->GetActorLocation()).GetSafeNormal();
		FVector MoveStep = Direction * MovementSpeed * DeltaTime;
		
		if (MoveStep.Size() > Distance)
		{
			MoveStep = (CurrentTarget->GetTargetPointLocation() - Army->GetActorLocation()).GetSafeNormal() * Distance;
		}
		
		// Move the army
		Army->SetActorLocation(Army->GetActorLocation() + MoveStep);
	}
}

void UArmyMovementComponent::Move(ATile* Tile)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MOVE THE ARMYyyyyyyyyyyyyyy!!!")));
	if (!Navigator) return;
	
	// Find the path
	Path = Navigator->GetPath(Army->Tile, Tile);
	
	// Make sure path is valid
	if (Path.Num() <= 0) return;
	
	// TODO: Do not calculate movement point again, when starting to move!!! Infinite movement glitch!!
	CalculateMovementPoints();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MOVE THE ARMY!!!")));
	
	bMoving = true;
	CurrentTarget = Path[0];
}

/**
 * Calculates army movement points as the minimum among all units.
 * Army movement is restricted by the slowest unit.
 */
void UArmyMovementComponent::CalculateMovementPoints()
{
	int32 Points = 1000000;
	for (auto& Unit : Army->Units)
	{
		if (Unit.MovementPoints < Points)
		{
			Points = Unit.MovementPoints;
		}
	}
	
	// Apply final number to the class variable
	this->MovementPoints = Points;
}
