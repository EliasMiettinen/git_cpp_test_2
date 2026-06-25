#pragma once
#include "CoreMinimal.h"
#include "BasePlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerPawn.generated.h"

class USpringActionComponent;
class UCameraComponent;

UCLASS()
class GIT_TEST_CPP_2_API APlayerPawn : public ABasePlayerPawn
{
	GENERATED_BODY()
	
public:
	APlayerPawn();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentMoveSpeed = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultMoveSpeed = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float FastMoveSpeed = 2000.0f;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;
	
	float CurrentMoveForwardValue = 0.0f;
	float CurrentMoveRightValue = 0.0f;
	
	float TargetCameraDistance = 700.0f;
	float CurrentCameraDistance = 700.0f;
	
#pragma region Movement
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void OnToggleSprint();
	void StopSprint();
	
	void OnMouseScroll(float Value);
	
#pragma endregion
};
