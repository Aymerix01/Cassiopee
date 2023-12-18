// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "MyEntityController.generated.h"


class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CASSIOPEE_API AMyEntityController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyEntityController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UNiagaraSystem* FXCursor;

	uint32 bMoveToMouseCursor : 1;

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FVector PlaceActorAroundBounds(FVector Origin, FVector Extent, float EntityIndex, float countEntity);
	UFUNCTION(BlueprintCallable)
	void TravelToDestination(FVector destination);
	UFUNCTION(BlueprintCallable)
	void TravelToNewBuilding(FVector destination);
	UFUNCTION(BlueprintCallable)
	bool HasReachedDestination(FVector destination) const;
	UFUNCTION(BlueprintCallable)
	bool IsMotionlessForSomeTime(float time) const;

	void MoveRandomly();
	void GetNavMeshBounds(TArray<FBox>& OutNavBounds);

	UPROPERTY(BlueprintReadWrite)
	bool IsArrivedToBuild;
	UPROPERTY(BlueprintReadWrite)
	FVector IADestination;
	UPROPERTY(BlueprintReadWrite)
	float timeBeforeMotionless;

private:
	APawn* ControlledPawn;

	float FollowTimeForIA;
	float IdleTimeBeforeRandomMove;
	float maxTimeWaitingMotionless;
};
