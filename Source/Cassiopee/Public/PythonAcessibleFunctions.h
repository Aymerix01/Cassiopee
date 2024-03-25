// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PythonAcessibleFunctions.generated.h"

/**
 * 
 */
UCLASS()
class CASSIOPEE_API UPythonAcessibleFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void P_K2_SynchronizeAndBroadcastDataChange(UObjectBase water);
	
};
