// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "WaterSplineComponent.h"
#include "Serialization/JsonSerializer.h"


/**
 * 
 */
class CASSIOPEE_API LakesLoader
{
public:
	static TSharedPtr<FJsonObject> loadJson(FString path);
	static void spawnLakes(TSharedPtr<FJsonObject> jsonFile, UWorld* world);
};
