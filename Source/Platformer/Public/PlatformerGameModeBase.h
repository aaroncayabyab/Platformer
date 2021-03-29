// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API APlatformerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Platformer")
	int32 CoinCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Platformer")
	int32 GemCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Platformer")
	bool bHasKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platformer")
	int32 DeathCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Platformer")
	FTransform SpawnLocation;

	UFUNCTION(BlueprintCallable, Category = "Platformer")
	void Respawn();

protected:
	UPROPERTY(EditAnywhere, Category = "Platformer")
	TSubclassOf<AActor> PlayerStart;
};
