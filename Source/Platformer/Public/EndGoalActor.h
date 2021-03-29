// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndGoalActor.generated.h"


class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class PLATFORMER_API AEndGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGoalActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Platformer")
	UStaticMeshComponent* MeshComp;


	UPROPERTY(VisibleAnywhere, Category = "Platformer")
	UCapsuleComponent* CapsuleCollisionComp;


	UPROPERTY(VisibleAnywhere, Category = "Platformer")
	USoundBase* EndGoalSound;

public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Platformer")
	void HandleLevelComplete();
};
