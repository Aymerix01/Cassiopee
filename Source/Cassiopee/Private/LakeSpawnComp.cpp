// Fill out your copyright notice in the Description page of Project Settings.


#include "LakeSpawnComp.h"

// Sets default values for this component's properties
ULakeSpawnComp::ULakeSpawnComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	splineComp = GetOwner()->FindComponentByClass<UWaterSplineComponent>();
}

void ULakeSpawnComp::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	splineComp->ResetSpline(splinePoints);
}


// Called when the game starts
void ULakeSpawnComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULakeSpawnComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

