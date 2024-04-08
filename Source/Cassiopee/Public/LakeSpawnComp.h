// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaterSplineComponent.h"
#include "LakeSpawnComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASSIOPEE_API ULakeSpawnComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULakeSpawnComp();

	virtual void OnConstruction(const FTransform& Transform);

	UPROPERTY(EditAnywhere)
	TArray<FVector> splinePoints;

	UWaterSplineComponent *splineComp;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
