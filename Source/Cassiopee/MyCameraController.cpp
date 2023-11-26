// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraController.h"
#include "MyEntityController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "MyEntity.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

AMyCameraController::AMyCameraController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
}

void AMyCameraController::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();

	if (World)
	{
		UClass* MyEntityPawnClass = LoadClass<APawn>(nullptr, TEXT("Blueprint'/Game/BP/BP_MyEntity.BP_MyEntity_C'"));
		if (MyEntityPawnClass)
		{
			FVector SpawnLocationValue(1200.0f, 0.0f, 0.0f);
			FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
			AActor* SpawnedPawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(World, MyEntityPawnClass, FTransform(SpawnRotation, SpawnLocationValue));
			UGameplayStatics::FinishSpawningActor(SpawnedPawn, FTransform(SpawnRotation, SpawnLocationValue));
			ControlledPawn = Cast<APawn>(SpawnedPawn);
		}
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMyCameraController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMyCameraController::StopMovement);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMyCameraController::FindHitLocation);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMyCameraController::CallEntityMovement);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMyCameraController::CallEntityMovement);
	}
}

void AMyCameraController::FindHitLocation()
{
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
}

void AMyCameraController::CallEntityMovement() 
{
	AMyEntityController* EntityController = ControlledPawn ? Cast<AMyEntityController>(ControlledPawn->GetController()) : nullptr;
	if (EntityController)
	{
		EntityController->TravelToDestination(CachedDestination);
	}
}