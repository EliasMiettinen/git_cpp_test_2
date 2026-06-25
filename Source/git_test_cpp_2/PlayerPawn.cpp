#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Create root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	// Create spring arm component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 700.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-65.0f, 0.0f, 0.0f));
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bDoCollisionTest = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
	// Initialize movespeed
	CurrentMoveSpeed = DefaultMoveSpeed;
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 51.f, FColor::Red, TEXT("Player Pawn Initialized------------------------------->>>>>>>>>>>>>"));
}

void APlayerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MouseScroll", this, &APlayerPawn::OnMouseScroll);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerPawn::OnToggleSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerPawn::StopSprint);
}

#pragma region Movement

void APlayerPawn::MoveForward(float Value)
{
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	CurrentMoveForwardValue = FMath::FInterpTo(CurrentMoveForwardValue, Value, DeltaSeconds, 10.0f + DeltaSeconds);
	AddActorWorldOffset(FVector(CurrentMoveForwardValue * DefaultMoveSpeed * DeltaSeconds, 0.0f, 0.0f));
}

void APlayerPawn::MoveRight(float Value)
{
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	CurrentMoveRightValue = FMath::FInterpTo(CurrentMoveRightValue, Value, DeltaSeconds, 10.0f + DeltaSeconds);
	AddActorWorldOffset(FVector(0.0f, CurrentMoveRightValue * DefaultMoveSpeed * DeltaSeconds, 0.0f));
}

void APlayerPawn::OnToggleSprint()
{
	CurrentMoveSpeed = FastMoveSpeed;
}

void APlayerPawn::StopSprint()
{
	CurrentMoveSpeed = DefaultMoveSpeed;
}

#pragma endregion

#pragma region Camera

void APlayerPawn::OnMouseScroll(float Value)
{
	TargetCameraDistance = FMath::Clamp(TargetCameraDistance + -Value * 100.0f, 700.0f, 1300.0f);
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	CurrentCameraDistance = FMath::FInterpTo(CurrentCameraDistance, TargetCameraDistance, DeltaSeconds, 10.0f + DeltaSeconds);
	SpringArmComponent->TargetArmLength = CurrentCameraDistance;
}

#pragma endregion