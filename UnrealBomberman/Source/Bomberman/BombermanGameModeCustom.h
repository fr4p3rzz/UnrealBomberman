// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameModeCustom.generated.h"

struct FBombermanPlayer
{
	APlayerController* PlayerController;
	FString AuthToken;
	bool bAuthenticated;

	FBombermanPlayer()
	{
		PlayerController = nullptr;
		bAuthenticated = true;
	}
};

UCLASS()
class BOMBERMAN_API ABombermanGameModeCustom : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABombermanGameModeCustom();

	void PostLogin(APlayerController* NewPlayer) override;
	
	TMap<APlayerController*, FBombermanPlayer> KnownPlayers;

	void Authenticate(APlayerController* PlayerController, const FString& AuthToken);
	void PlayerDie(APlayerController* PlayerController);

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PlayingPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> SpectatorPawn;
};
