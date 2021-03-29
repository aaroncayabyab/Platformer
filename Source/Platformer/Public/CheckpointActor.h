// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"


class UStaticMeshComponent;
class USphereComponent;
class USoundBase;

UCLASS()
class PLATFORMER_API ACheckpointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platformer")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platformer")
	USphereComponent* SphereCollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platformer")
	bool bCheckpointEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platformer")
	float SpawnZOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platformer")
	USoundBase* CheckpointSound;

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
