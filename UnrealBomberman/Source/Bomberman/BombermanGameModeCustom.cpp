// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanGameModeCustom.h"

ABombermanGameModeCustom::ABombermanGameModeCustom()
{
}

void ABombermanGameModeCustom::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("New Player connected: %s"), *NewPlayer->GetFullName());

	FBombermanPlayer NewPlayerData;
	KnownPlayers.Add(NewPlayer, NewPlayerData);
}

void ABombermanGameModeCustom::Authenticate(APlayerController* PlayerController, const FString& AuthToken)
{
	if (KnownPlayers.Contains(PlayerController))
	{
		FBombermanPlayer& PlayerData = KnownPlayers[PlayerController];
		PlayerData.AuthToken = AuthToken;
		PlayerData.bAuthenticated = true;

		FTransform Transform;

		APawn* CurrentPawn = PlayerController->GetPawn();
		if (CurrentPawn)
		{
			Transform = CurrentPawn->GetActorTransform();
		}

		Transform.AddToTranslation(FVector(0, 0, 200));

		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(PlayingPawn, Transform);
		if (NewPawn)
		{
			PlayerController->UnPossess();
			PlayerController->Possess(NewPawn);
			if (CurrentPawn)
			{
				CurrentPawn->Destroy();
			}
		}
	}
}

void ABombermanGameModeCustom::PlayerDie(APlayerController* PlayerController)
{
	if (KnownPlayers.Contains(PlayerController))
	{
		FBombermanPlayer& PlayerData = KnownPlayers[PlayerController];
		PlayerData.bAuthenticated = false;

		FTransform Transform;

		APawn* CurrentPawn = PlayerController->GetPawn();
		if (CurrentPawn)
		{
			Transform = CurrentPawn->GetActorTransform();
		}

		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(SpectatorPawn, Transform);
		if (NewPawn)
		{
			PlayerController->UnPossess();
			PlayerController->Possess(NewPawn);
			if (CurrentPawn)
			{
				CurrentPawn->Destroy();
			}
		}
	}
}
