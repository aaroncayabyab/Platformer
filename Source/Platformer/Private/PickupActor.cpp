// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupActor::APickupActor()
{

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>("SphereCollisionComp");
	SphereCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnOverlap);
	SphereCollisionComp->SetSphereRadius(64.0f);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PickupMeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = SphereCollisionComp;
	MeshComp->SetupAttachment(RootComponent);
}

void APickupActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandlePickup();
	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	Destroy();
}

