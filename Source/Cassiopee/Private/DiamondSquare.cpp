// Fill out your copyright notice in the Description page of Project Settings.


#include "DiamondSquare.h"
#include "ProceduralMeshComponent.h" 
#include "KismetProceduralMeshLibrary.h"

ADiamondSquare::ADiamondSquare()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	ProceduralMesh->SetMobility(EComponentMobility::Static);
	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProceduralMesh->SetupAttachment(GetRootComponent());
	ProceduralMesh->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = ProceduralMesh;
}

// Called when the game starts or when spawned
void ADiamondSquare::BeginPlay()
{
	Super::BeginPlay();

}

void ADiamondSquare::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

// Called every frame
void ADiamondSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADiamondSquare::CreateVertices()
{
	for (int X = 0; X <= Size; ++X)
	{
		for (int Y = 0; Y <= Size; ++Y)
		{
			float Z = FMath::PerlinNoise2D(FVector2D((X + XOffset) * NoiseScale, (Y + YOffset) * NoiseScale)) * ZMultiplier;
			// GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z));
			Vertices.Add(FVector((X - Size / 2) * VertexDistance, (Y - Size / 2) * VertexDistance, Z));
			UV0.Add(FVector2D((X - Size / 2) * UVScale, (Y - Size / 2) * UVScale));

			// Debug
			// DrawDebugSphere(GetWorld(), FVector(X * Scale, Y * Scale, 0), 25.0f, 16, FColor::Red, true);
		}
	}
}


void ADiamondSquare::CreateTriangles()
{
	int Vertex = 0;

	for (int X = 0; X < Size; X++)
	{
		for (int Y = 0; Y < Size; Y++)
		{
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + Size + 1);

			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + Size + 2);
			Triangles.Add(Vertex + Size + 1);

			Vertex++;
		}
		Vertex++;
	}
}


void ADiamondSquare::SetSize(int NScale)
{
	Size = NScale;
}


void ADiamondSquare::SetScale(int NScale)
{
	VertexDistance = NScale;
}

void ADiamondSquare::SetUVScale(int NScale)
{
	UVScale = NScale;
}

void ADiamondSquare::SetZMultiplier(float NScale)
{
	ZMultiplier = NScale;
}

void ADiamondSquare::SetNoiseScale(float NScale)
{
	NoiseScale = NScale;
}

void ADiamondSquare::Generate()
{
	Vertices.Reset();
	Triangles.Reset();
	UV0.Reset();

	CreateVertices();
	CreateTriangles();

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, TArray<FColor>(), Tangents, true);
	ProceduralMesh->SetMaterial(0, Material);
}

void ADiamondSquare::SetXOffset(float NXOffset)
{
	XOffset = NXOffset;
}

void ADiamondSquare::SetYOffset(float NYOffset)
{
	YOffset = NYOffset;
}