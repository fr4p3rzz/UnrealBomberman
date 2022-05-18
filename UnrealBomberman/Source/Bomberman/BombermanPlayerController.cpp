// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanPlayerController.h"
#include "BombermanGameModeCustom.h"

ABombermanPlayerController::ABombermanPlayerController()
{
	bShowMouseCursor = true;
}

void ABombermanPlayerController::Authenticate_Implementation(const FString& AuthToken)
{
	UE_LOG(LogTemp, Warning, TEXT("Player %s sent AuthCode %s"), *GetFullName(), *AuthToken);

	ABombermanGameModeCustom* GameMode = GetWorld()->GetAuthGameMode<ABombermanGameModeCustom>();
	if (GameMode)
	{
		GameMode->Authenticate(this, AuthToken);
	}
}

void ABombermanPlayerController::Die_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Player %s die"), *GetFullName());

	ABombermanGameModeCustom* GameMode = GetWorld()->GetAuthGameMode<ABombermanGameModeCustom>();
	if (GameMode)
	{
		GameMode->PlayerDie(this);
	}
}
