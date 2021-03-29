// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGoalActor.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.h"

// Sets default values
AEndGoalActor::AEndGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollisionComp"));
	CapsuleCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CapsuleCollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void AEndGoalActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		HandleLevelComplete();
	}
}

