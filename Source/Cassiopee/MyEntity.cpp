// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyEntity.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AMyEntity::AMyEntity()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyEntity::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add("Korogu");
	UClass* MyEntityControllerClass = LoadClass<APlayerController>(nullptr, TEXT("Blueprint'/Game/BP/BP_MyEntityController.BP_MyEntityController_C'"));
	if (MyEntityControllerClass)
	{
		APlayerController* NewController = GetWorld()->SpawnActor<APlayerController>(MyEntityControllerClass, FVector::ZeroVector, FRotator::ZeroRotator);

		if (NewController)
		{
			this->Controller = NewController;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create MyEntityController instance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load MyEntityController class"));
	}
}
