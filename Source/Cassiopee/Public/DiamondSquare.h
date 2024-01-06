// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "DiamondSquare.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class CASSIOPEE_API ADiamondSquare : public AActor
{
	GENERATED_BODY()

	public:
		// Sets default values for this actor's properties
		ADiamondSquare();

		UPROPERTY(EditAnywhere, BlueprintSetter = SetSize, Meta = (ClampMin = 0))
		int Size = 0;

		UPROPERTY(EditAnywhere, BlueprintSetter = SetScale, Meta = (ClampMin = 0.000001))
		int VertexDistance = 100;

		UPROPERTY(EditAnywhere, BlueprintSetter = SetUVScale, Meta = (ClampMin = 0.000001))
		int UVScale = 1;

		UPROPERTY(EditAnywhere, BlueprintSetter = SetZMultiplier, Meta = (ClampMin = 0))
		float ZMultiplier = 1000.0f;

		UPROPERTY(EditAnywhere, BlueprintSetter = SetNoiseScale, Meta = (ClampMin = 0))
		float NoiseScale = 1.0f;

		UPROPERTY(EditAnywhere, BlueprintSetter = SetXOffset)
		float XOffset;

		UPROPERTY(EditAnywhere, BlueprintSetter = SetYOffset)
		float YOffset;

		UFUNCTION(BlueprintSetter)
		void SetSize(int NScale);

		UFUNCTION(BlueprintSetter)
		void SetScale(int NScale);

		UFUNCTION(BlueprintSetter)
		void SetUVScale(int NScale);

		UFUNCTION(BlueprintSetter)
		void SetZMultiplier(float NScale);

		UFUNCTION(BlueprintSetter)
		void SetNoiseScale(float NScale);

		UFUNCTION(BlueprintCallable)
		void Generate();

		UFUNCTION(BlueprintSetter)
		void SetXOffset(float NXOffset);

		UFUNCTION(BlueprintSetter)
		void SetYOffset(float NYOffset);


	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		virtual void OnConstruction(const FTransform& Transform) override;

		UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;


	private:
		UProceduralMeshComponent* ProceduralMesh;
		TArray<FVector> Vertices;
		TArray<int> Triangles;
		TArray<FVector2D> UV0;
		TArray<FVector> Normals;
		TArray<FProcMeshTangent> Tangents;

		void CreateVertices();
		void CreateTriangles();
};
