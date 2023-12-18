// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEntityController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "MyEntity.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationSystem.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"


AMyEntityController::AMyEntityController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	IsArrivedToBuild = true;
	IADestination = FVector::ZeroVector;
	FollowTimeForIA = 0.f;
	timeBeforeMotionless = 0.f;
	IdleTimeBeforeRandomMove = 5.f;
	maxTimeWaitingMotionless = 10.f;
}

void AMyEntityController::BeginPlay()
{
	Super::BeginPlay();
	ControlledPawn = GetPawn();
	IADestination = ControlledPawn->GetActorLocation();
}

FVector AMyEntityController::PlaceActorAroundBounds(FVector Origin, FVector Extent, float EntityIndex, float countEntity) 
{
	UWorld* World = GetWorld();
	ACharacter* MyCharacter = Cast<ACharacter>(ControlledPawn);
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to access the world."));
		return FVector(0, 0, 0);
	}

	float largeur = FMath::Abs(Extent.Y)*2;
	float longueur = FMath::Abs(Extent.X)*2;
	
	float perimetre = longueur * 2 + largeur * 2;
	float posEntityOnPerimetre = (perimetre / countEntity) * EntityIndex;

	FVector posResult;

	if (posEntityOnPerimetre < longueur) {
		posResult =  Origin + FVector(posEntityOnPerimetre - longueur/2, - largeur/2, 0);
	}
	else if (posEntityOnPerimetre < longueur + largeur) {
		posResult = Origin + FVector(longueur/2, posEntityOnPerimetre - longueur - largeur / 2, 0);
	}
	else if (posEntityOnPerimetre < 2 * longueur + largeur) {
		posResult = Origin + FVector(posEntityOnPerimetre - 2 * longueur - largeur + longueur / 2, largeur/2, 0);
	}
	else {
		posResult = Origin + FVector(-longueur/2, posEntityOnPerimetre - 2 * longueur - 2 * largeur + largeur / 2, 0);
	}
	return posResult;
	//UE_LOG(LogTemp, Warning, TEXT("Vector: X = %f, Y = %f, Z = %f"), RandomLocation.X, RandomLocation.Y, RandomLocation.Z);
}

void AMyEntityController::TravelToDestination(FVector destination)
{
	if (ControlledPawn != nullptr)
	{
		IADestination = destination;
		FVector WorldDirection = (destination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		FRotator NewControlRotation = WorldDirection.Rotation();
		SetControlRotation(NewControlRotation);
		ACharacter* MyCharacter = Cast<ACharacter>(ControlledPawn);
		if (MyCharacter)
		{
			UCharacterMovementComponent* MovementComponent = MyCharacter->GetCharacterMovement();
			if (MovementComponent)
			{
				MovementComponent->MaxWalkSpeed = 400.0f;
				MovementComponent->MaxAcceleration = 1000.0f;
			}
		}
		MoveToLocation(destination);
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, destination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, destination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void AMyEntityController::TravelToNewBuilding(FVector destination)
{
	if (ControlledPawn != nullptr)
	{
		IADestination = destination;
		FVector WorldDirection = (destination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		FRotator NewControlRotation = WorldDirection.Rotation();
		SetControlRotation(NewControlRotation);
		ACharacter* MyCharacter = Cast<ACharacter>(ControlledPawn);
		if (MyCharacter)
		{
			UCharacterMovementComponent* MovementComponent = MyCharacter->GetCharacterMovement();
			if (MovementComponent)
			{
				MovementComponent->MaxWalkSpeed = 400.0f;
				MovementComponent->MaxAcceleration = 1000.0f;
			}
		}
		MoveToLocation(destination);
		IsArrivedToBuild = false;
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, destination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, destination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

bool AMyEntityController::HasReachedDestination(FVector destination) const
{
	if (ControlledPawn)
	{
		FVector CurrentLocation = FVector(ControlledPawn->GetActorLocation().X, ControlledPawn->GetActorLocation().Y, ControlledPawn->GetActorLocation().Z-97.f);
		float DistanceSquared = FVector::DistSquared(CurrentLocation, destination);
		float ToleranceSquared = 200.0f * 200.0f;

		return DistanceSquared <= ToleranceSquared;
	}
	return true;
}
bool AMyEntityController::IsMotionlessForSomeTime(float time) const
{
	//UE_LOG(LogTemp, Warning, TEXT("Vector: X = %f, Y = %f, Z = %f"), ControlledPawn->GetVelocity().X, ControlledPawn->GetVelocity().Y, ControlledPawn->GetVelocity().Z);
	//UE_LOG(LogTemp, Warning, TEXT("Time: t = %f"), time);
	if (ControlledPawn && time > maxTimeWaitingMotionless && ControlledPawn->GetVelocity() == FVector(0, 0, 0)) {
		return true;
	}
	return false;
}

void AMyEntityController::GetNavMeshBounds(TArray<FBox>& OutNavBounds)
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSystem)
	{
		const ANavigationData* NavData = NavSystem->GetDefaultNavDataInstance();
		if (NavData)
		{
			OutNavBounds = NavData->GetNavigableBounds();
		}
	}
}

void AMyEntityController::MoveRandomly()
{
	TArray<FBox> NavBounds;
	GetNavMeshBounds(NavBounds);

	if (ControlledPawn != nullptr)
	{
		int32 RandomIndex = FMath::RandRange(0, NavBounds.Num() - 1);
		FBox RandomNavBound = NavBounds[RandomIndex];
		IADestination = FMath::RandPointInBox(RandomNavBound);
		TravelToDestination(IADestination);
	}
}

void AMyEntityController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ControlledPawn != nullptr)
	{
		timeBeforeMotionless += DeltaTime;
		if ((HasReachedDestination(IADestination) || IsMotionlessForSomeTime(timeBeforeMotionless)) && IsArrivedToBuild)
		{	
			FollowTimeForIA += DeltaTime;
			if (FollowTimeForIA >= IdleTimeBeforeRandomMove)
			{
				MoveRandomly();
				IsArrivedToBuild = true;
				FollowTimeForIA = 0.0f;
			}
		}
	}
}