// Fill out your copyright notice in the Description page of Project Settings.


#include "LakesLoader.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Landscape.h"
#include "Kismet/GameplayStatics.h" 
#include "Engine/Blueprint.h"
#include "CustomBodyLakeComponent.h"

#define BASE_LAKE_PATH "/Script/Engine.Blueprint'/Game/BP/Landscape/ProceduralLakes/BaseLake.BaseLake'"


TSharedPtr<FJsonObject> LakesLoader::loadJson(FString path)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path)) {
		UE_LOG(LogTemp, Warning, TEXT("Not able to read the path : %s"), *path);
		return TSharedPtr<FJsonObject>();
	}

	FString strFile = "";

	if (!FFileHelper::LoadFileToString(strFile, *path)) {
		UE_LOG(LogTemp, Warning, TEXT("Not able to read the file"));
		return TSharedPtr<FJsonObject>();
	}

	TSharedPtr<FJsonObject> jsonFile;

	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(strFile), jsonFile)) {
		UE_LOG(LogTemp, Warning, TEXT("Not able to read the file (not a JSON file)"));
		return TSharedPtr<FJsonObject>();
	}

	return jsonFile;
}

void LakesLoader::spawnLakes(TSharedPtr<FJsonObject> jsonFile, UWorld* world)
{
	ALandscape* landscape = (ALandscape*)UGameplayStatics::GetActorOfClass(world, ALandscape::StaticClass());

	if (!landscape) {
		UE_LOG(LogTemp, Warning, TEXT("Landscape not found"));
		return;
	}

	if (ULandscapeComponent* comp = landscape->FindComponentByClass<ULandscapeComponent>()) {
		ULandscapeInfo* info = comp->GetLandscapeInfo();

		// On suppose le landscape de forme carré

		FString path = BASE_LAKE_PATH;

		UBlueprint* bp = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *path));

		if (!bp) {
			UE_LOG(LogTemp, Warning, TEXT("Cannot load blueprint in %s"), BASE_LAKE_PATH);
			return;
		}

		FVector landOrigin, landBox, landBoundOrigin;
		landscape->GetActorBounds(false, landBoundOrigin, landBox, false);
		landOrigin = landscape->GetActorLocation();
		int minX = landOrigin.X, maxX = landBoundOrigin.X + landBox.X, minY = landOrigin.Y;
		int lakesSize = jsonFile->GetObjectField("dim")->GetIntegerField("x");

		float rapp = (float)(maxX - minX) / (float)lakesSize;

		/*UE_LOG(LogTemp, Log, TEXT("rapp : %d"), rapp);
		UE_LOG(LogTemp, Log, TEXT("lakesSize : %d"), lakesSize);
		UE_LOG(LogTemp, Log, TEXT("maxX : %d"), maxX);
		UE_LOG(LogTemp, Log, TEXT("minX : %d"), minX);*/

		FCollisionQueryParams collisionParams(FName(TEXT("FoliageClusterPlacementTrace")), true, nullptr);
		collisionParams.bReturnPhysicalMaterial = true;

		for (TSharedPtr< FJsonValue > lakeVar : jsonFile->GetArrayField("lakes")) {
			TArray< TSharedPtr< FJsonValue > > points = lakeVar->AsArray();

			float zHeight = 0;
			FVector sum = FVector::Zero();

			TArray<FVector> LakePoints;	

			for (int i = 0; i < points.Num(); i++){
				TSharedPtr< FJsonObject > point = points[i]->AsObject();
				LakePoints.Add(FVector(minX + rapp * point->GetIntegerField("x"), minY + rapp * point->GetIntegerField("y"), 0));
				//UE_LOG(LogTemp, Log, TEXT("Point at position : x : %f ; y : %f"), minX + rapp * point->GetIntegerField("x"), minY + rapp * point->GetIntegerField("y"));
				sum += FVector(minX + rapp * point->GetIntegerField("x"), minY + rapp * point->GetIntegerField("y"), 0);
			}

			FVector center = sum / points.Num();
			FHitResult hit(ForceInit);


			if (landscape->ActorLineTraceSingle(hit, center + FVector::UpVector * 10000, center - FVector::UpVector * 10000, ECC_Visibility, collisionParams)) {
				zHeight = hit.ImpactPoint.Z - 100;
				//UE_LOG(LogTemp, Log, TEXT("Collision !!"), maxX);
			}

			// DrawDebugLine(world, center - 10000 * FVector::UpVector, center + 10000 * FVector::UpVector, FColor::Red, true);

			AActor* lake = world->SpawnActor(bp->GeneratedClass);
			lake->SetActorLocation(FVector(0., 0., zHeight), false, nullptr, ETeleportType::None);
			UCustomBodyLakeComponent* watComp = lake->FindComponentByClass<UCustomBodyLakeComponent>();

			watComp->SetLakePoints(LakePoints);
			watComp->UpdateLake();
		}
	}
}
