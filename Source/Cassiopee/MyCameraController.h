// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyCameraController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CASSIOPEE_API AMyCameraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyCameraController();

	UPROPERTY(EditAnywhere)
		float EntityNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		float ShortPressThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UNiagaraSystem* FXCursor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* SetDestinationClickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* SetDestinationTouchAction;

protected:
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay();

	void FindHitLocation();
	void CallEntityMovement();

private:
	FVector CachedDestination;
	TArray<APawn*> MyEntityArray;
};
