// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointActor.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PlatformerGameModeBase.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	SphereCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereCollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	bCheckpointEnabled = false;
	SpawnZOffset = 100.0f;

}

// Called when the game starts or when spawned
void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpointActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (bCheckpointEnabled == false)
	{
		bCheckpointEnabled = true;
		APlatformerGameModeBase* GameMode = Cast<APlatformerGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CheckpointSound, GetActorLocation());
			FTransform SpawnTransform = GetActorTransform();
			FVector SpawnPosition = SpawnTransform.GetLocation() + FVector(0, 0, SpawnZOffset);
			SpawnTransform.SetLocation(SpawnPosition);
			GameMode->SpawnLocation = SpawnTransform;
		}
	}
}

