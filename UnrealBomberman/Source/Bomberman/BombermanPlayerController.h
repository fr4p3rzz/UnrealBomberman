// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BombermanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABombermanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABombermanPlayerController();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Authenticate(const FString& AuthToken);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Die();
	
};
