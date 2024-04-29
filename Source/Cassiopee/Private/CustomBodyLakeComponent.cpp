// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBodyLakeComponent.h"

// Sets default values for this component's properties
UCustomBodyLakeComponent::UCustomBodyLakeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	AActor* Owner = GetOwner();

	if (Owner != nullptr) {
		WaterBodyComponent = Owner->FindComponentByClass<UWaterBodyComponent>();
		WaterSpline = Owner->FindComponentByClass<UWaterSplineComponent>();
	}

	LakePoints.Init(FVector::ZeroVector, 0);
}


#if WITH_EDITOR
void UCustomBodyLakeComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UCustomBodyLakeComponent, LakePoints)) {
		WaterSpline->ClearSplinePoints(false);
		for (const FVector& splinePoint : LakePoints) {
			WaterSpline->AddSplinePoint(splinePoint, ESplineCoordinateSpace::World, false);
		}
		WaterSpline->UpdateSpline();
		WaterSpline->K2_SynchronizeAndBroadcastDataChange();
	}
}
#endif // WITH_EDITOR

// Called when the game starts
void UCustomBodyLakeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCustomBodyLakeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

