// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanJsonMapReader.h"
#include "AssetRegistryModule.h"
#include "Engine/StaticMeshActor.h"
#include "Factories/WorldFactory.h"
#include "Misc/FileHelper.h"

#include "Engine/DirectionalLight.h"

#define LOCTEXT_NAMESPACE "FBombermanJsonMapReaderModule"

void FBombermanJsonMapReaderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	MapCreateActor.Add("0", &FBombermanJsonMapReaderModule::CreatePlatform);
	MapCreateActor.Add("1", &FBombermanJsonMapReaderModule::CreateBreakableWall);
	MapCreateActor.Add("2", &FBombermanJsonMapReaderModule::CreateUnbreakableWall);
}

void FBombermanJsonMapReaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

}
//"D:\CORSO AIV 2021-2022\EsercitazioniStudenti\Level01.txt"
bool FBombermanJsonMapReaderModule::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	if (FParse::Command(&Cmd, TEXT("newlevel")))
	{
		FString Path = FParse::Token(Cmd, true);
		UE_LOG(LogTemp, Error, TEXT("%s"), *Path);
		TArray<FString> FileArr;
		FFileHelper::LoadFileToStringArray(FileArr, *Path);
		int32 StartX = 0;
		int32 StartY = 0;
		int32 Size = 100;
		if (FileArr.Num() > 0)
		{
			UWorldFactory* NewWorld = NewObject<UWorldFactory>();

			uint64 SuffixAssetName = FPlatformTime::Cycles64();
			FString AssetName = FString::Printf(TEXT("M_NewLevel_%llu"), SuffixAssetName);
			UPackage* Package = CreatePackage(*FString::Printf(TEXT("/Game/%s"), *AssetName));

			UObject* NewLevelObject = NewWorld->FactoryCreateNew(NewWorld->SupportedClass, Package, *AssetName, EObjectFlags::RF_Standalone | EObjectFlags::RF_Public, nullptr, GWarn);
			FAssetRegistryModule::AssetCreated(NewLevelObject);

			UWorld* WorldCasted = Cast<UWorld>(NewLevelObject);
			WorldCasted->Modify();

			WorldCasted->SpawnActor<ADirectionalLight>();

			for (FString Line : FileArr)
			{
				UE_LOG(LogTemp, Error, TEXT("%s"), *Line);
				TArray<FString> BlockInLine;
				Line.ParseIntoArray(BlockInLine, TEXT(","));
				for (int32 Index = 0; Index < BlockInLine.Num(); Index++)
				{
					(this->* * MapCreateActor.Find("0"))(WorldCasted, StartX * Size, StartY * Size);
					if (BlockInLine[Index].Equals("0"))
					{
						++StartX;
						continue;
					}
					(this->* * MapCreateActor.Find(BlockInLine[Index]))(WorldCasted, StartX * Size, StartY * Size);

					++StartX;
				}
				++StartY;
				StartX = 0;
			}
			WorldCasted->PostEditChange();
			WorldCasted->MarkPackageDirty();
		}

		return true;
	}

	return false;
}
//StaticMesh'/Game/Geometry/Meshes/TemplateFloor.TemplateFloor'
AActor* FBombermanJsonMapReaderModule::CreatePlatform(UWorld* InWorld, const int32 InX, const int32 InY)
{
	AStaticMeshActor* MyActor = InWorld->SpawnActor<AStaticMeshActor>();
	FVector MyLocation = FVector(InX, InY, -50);
	FTransform MyTransform;
	MyTransform.AddToTranslation(MyLocation);
	MyActor->SetActorTransform(MyTransform);
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(nullptr, *FString("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	MyActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
	return MyActor;
}

AActor* FBombermanJsonMapReaderModule::CreateUnbreakableWall(UWorld* InWorld, const int32 InX, const int32 InY)
{
	AStaticMeshActor* MyActor = InWorld->SpawnActor<AStaticMeshActor>();
	FVector MyLocation = FVector(InX, InY, 0);
	FTransform MyTransform; 
	MyTransform.AddToTranslation(MyLocation);
	MyActor->SetActorTransform(MyTransform);
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(nullptr, *FString("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	MyActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
	return MyActor;
}

AActor* FBombermanJsonMapReaderModule::CreateBreakableWall(UWorld* InWorld, const int32 InX, const int32 InY)
{
	AStaticMeshActor* MyActor = InWorld->SpawnActor<AStaticMeshActor>();
	FVector MyLocation = FVector(InX, InY, 0);
	FTransform MyTransform;
	MyTransform.AddToTranslation(MyLocation);
	MyActor->SetActorTransform(MyTransform);
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(nullptr, *FString("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	MyActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
	return MyActor;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBombermanJsonMapReaderModule, BombermanJsonMapReader)