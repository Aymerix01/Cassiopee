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
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"


AMyEntityController::AMyEntityController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	IADestination = FVector::ZeroVector;
	FollowTimeForIA = 0.f;
	IdleTimeBeforeRandomMove = 5.f;
}

void AMyEntityController::BeginPlay()
{
	Super::BeginPlay();
	ControlledPawn = GetPawn();
	IADestination = ControlledPawn->GetActorLocation();
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
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, destination);
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
		if (!IsMoveInputIgnored() && HasReachedDestination(IADestination))
		{
			FollowTimeForIA += DeltaTime;
			if (FollowTimeForIA >= IdleTimeBeforeRandomMove)
			{
				MoveRandomly();
				FollowTimeForIA = 0.0f;
			}
		}
		else
		{
			FollowTimeForIA = 0.0f;
		}
	}
}