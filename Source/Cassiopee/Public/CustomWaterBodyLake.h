// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WaterBodyLakeActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomWaterBodyLake.generated.h"

UCLASS()
class CASSIOPEE_API ACustomWaterBodyLake : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomWaterBodyLake();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AWaterBody> WaterBody;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
