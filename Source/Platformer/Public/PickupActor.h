// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class USoundBase;

UCLASS()
class PLATFORMER_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:

	UPROPERTY(EditAnywhere, Category = "Platformer")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Platformer")
	USphereComponent* SphereCollisionComp;

	UPROPERTY(EditAnywhere, Category = "Platformer")
	USoundBase* PickupSound;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "Platformer")
	void HandlePickup();
};
