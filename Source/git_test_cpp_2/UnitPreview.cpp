#include "UnitPreview.h"

AUnitPreview::AUnitPreview()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AUnitPreview::BeginPlay()
{
	Super::BeginPlay();
}

void AUnitPreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
