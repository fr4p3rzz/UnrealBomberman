// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBombermanJsonMapReaderModule : public IModuleInterface, public FSelfRegisteringExec
{
public:
	typedef AActor* (FBombermanJsonMapReaderModule::* CreateActor)(UWorld*, const int32, const int32);

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	AActor* CreatePlatform(UWorld* InWorld, const int32 InX, const int32 InY);
	AActor* CreateUnbreakableWall(UWorld* InWorld, const int32 InX, const int32 InY);
	AActor* CreateBreakableWall(UWorld* InWorld, const int32 InX, const int32 InY);

	TMap<FString, CreateActor> MapCreateActor;
};
