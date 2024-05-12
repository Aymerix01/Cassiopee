// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBodyLakeComponent.h"
#include "Serialization/JsonSerializer.h"

// Sets default values for this component's properties
UCustomBodyLakeComponent::UCustomBodyLakeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	AActor* Owner = GetOwner();

	//UE_LOG(LogTemp, Log, TEXT("Owner address : %p"), Owner);

	if (Owner != nullptr) {
		WaterBodyComponent = Owner->FindComponentByClass<UWaterBodyComponent>();
		WaterSpline = Owner->FindComponentByClass<UWaterSplineComponent>();
	}

	//UE_LOG(LogTemp, Log, TEXT("WaterBodyComponent address : %p"), WaterBodyComponent);
	//UE_LOG(LogTemp, Log, TEXT("WaterSpline address : %p"), WaterSpline);

	LakePoints.Init(FVector::ZeroVector, 0);
}

void UCustomBodyLakeComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//UE_LOG(LogTemp, Log, TEXT("Is WaterSpline null : %d"), WaterSpline == nullptr);
	//UE_LOG(LogTemp, Log, TEXT("WaterSpline address : %p"), WaterSpline);
	//UE_LOG(LogTemp, Log, TEXT("nullptdr address : %p"), nullptr);	

	WaterSpline = GetOwner()->FindComponentByClass<UWaterSplineComponent>();
	WaterBodyComponent = GetOwner()->FindComponentByClass<UWaterBodyComponent>();

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UCustomBodyLakeComponent, LakePoints))
		UpdateLake();
}

void UCustomBodyLakeComponent::UpdateLake()
{
	WaterSpline = GetOwner()->FindComponentByClass<UWaterSplineComponent>();
	WaterBodyComponent = GetOwner()->FindComponentByClass<UWaterBodyComponent>();
	if (WaterSpline && WaterBodyComponent) {
		WaterSpline->ResetSpline(LakePoints);
		WaterSpline->K2_SynchronizeAndBroadcastDataChange();
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("WaterSpline or WaterBodyComponent is null."));
}

void UCustomBodyLakeComponent::SetLakePoints(TArray<FVector> points)
{
	LakePoints = points;
}

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

}

