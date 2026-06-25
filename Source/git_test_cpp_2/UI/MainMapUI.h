#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMapUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextTurnClicked);

UCLASS()
class GIT_TEST_CPP_2_API UMainMapUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bEnabled;
	
	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnEnableTurn();
	
	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnEndTurn();
	
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FOnNextTurnClicked OnNextTurnClicked;
	
	UFUNCTION(BlueprintCallable, Category = "UI Events")
	void NextTurn();
};
