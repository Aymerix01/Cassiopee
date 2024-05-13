// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomWaterBodyLake.h"

// Sets default values
ACustomWaterBodyLake::ACustomWaterBodyLake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WaterBody = CreateDefaultSubobject<AWaterBody>(TEXT("WaterBody"));

}

// Called when the game starts or when spawned
void ACustomWaterBodyLake::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomWaterBodyLake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

