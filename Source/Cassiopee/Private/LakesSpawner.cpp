// Fill out your copyright notice in the Description page of Project Settings.


#include "LakesSpawner.h"
#include "LakesLoader.h"

// Sets default values
ALakesSpawner::ALakesSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALakesSpawner::spawnLakes()
{
	LakesLoader::spawnLakes(LakesLoader::loadJson(jsonPath), GetWorld());
}

// Called when the game starts or when spawned
void ALakesSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALakesSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

