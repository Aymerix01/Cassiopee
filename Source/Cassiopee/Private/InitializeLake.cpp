// Fill out your copyright notice in the Description page of Project Settings.


#include "InitializeLake.h"
#include "WaterBodyLakeActor.h"

// Sets default values for this component's properties
UInitializeLake::UInitializeLake()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInitializeLake::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UInitializeLake::OnComponentCreated() {
	UE_LOG(LogTemp, Warning, TEXT("OnComponentCreated"));
	FActorSpawnParameters par;
	AWaterBodyLake* lake = GetWorld()->SpawnActor<AWaterBodyLake>(par);
}

// Called every frame
void UInitializeLake::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

