// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WaterBodyLakeActor.h"
#include "WaterSplineComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomBodyLakeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASSIOPEE_API UCustomBodyLakeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomBodyLakeComponent();

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif // WITH_EDITOR

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UWaterBodyComponent> WaterBodyComponent;

	UPROPERTY(EditAnywhere)
	TArray<FVector> LakePoints;

	UPROPERTY()
	TObjectPtr<UWaterSplineComponent> WaterSpline;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
