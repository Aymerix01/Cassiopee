// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InitializeLake.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASSIOPEE_API UInitializeLake : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInitializeLake();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
