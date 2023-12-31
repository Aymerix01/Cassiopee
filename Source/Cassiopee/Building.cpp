// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::RotateBuilding()
{
    // Get the current rotation
    FRotator CurrentRotation = GetActorRotation();

    // Add 90 degrees to the Yaw (you can customize this as needed)
    CurrentRotation.Yaw += 90.0f;

    // Set the new rotation
    SetActorRotation(CurrentRotation);
}

