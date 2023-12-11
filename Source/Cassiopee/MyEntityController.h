// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "MyEntityController.generated.h"


class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CASSIOPEE_API AMyEntityController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyEntityController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UNiagaraSystem* FXCursor;

	uint32 bMoveToMouseCursor : 1;

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	void TravelToDestination(FVector destination);
	bool HasReachedDestination(FVector destination) const;

	void MoveRandomly();
	void GetNavMeshBounds(TArray<FBox>& OutNavBounds);

private:
	FVector IADestination;
	APawn* ControlledPawn;

	float FollowTimeForIA;
	float IdleTimeBeforeRandomMove;
};
