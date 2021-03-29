// Copyright Epic Games, Inc. All Rights Reserved.


#include "PlatformerGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlatformerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	DeathCount = 0;
	CoinCount = 0;
	GemCount = 0;
	bHasKey = false;

	AActor* PlayerStartActor = UGameplayStatics::GetActorOfClass(this, PlayerStart);
	if (ensure(PlayerStartActor))
	{
		SpawnLocation = PlayerStartActor->GetActorTransform();
	}
}

void APlatformerGameModeBase::Respawn()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			RestartPlayerAtTransform(PC, SpawnLocation);
		}
	}
}
