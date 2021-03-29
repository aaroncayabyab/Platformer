// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlatformerGameModeBase.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	CharacterMovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (ensure(CharacterMovementComp))
	{
		CharacterMovementComp->GetNavAgentPropertiesRef().bCanCrouch = true;
		CharacterMovementComp->bOrientRotationToMovement = true;
		DefaultSpeed = CharacterMovementComp->GetMaxSpeed();
		SprintSpeed = DefaultSpeed * 2.0f;
	}
	Health = 100.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::MoveForward(float Value)
{
	const FVector WorldForwardVector = 
		UKismetMathLibrary::GetForwardVector(
			FRotator(0, GetControlRotation().Yaw, 0));
	AddMovementInput(WorldForwardVector * Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	const FVector WorldRightVector =
		UKismetMathLibrary::GetRightVector(
			FRotator(0, GetControlRotation().Yaw, 0));
	AddMovementInput(WorldRightVector * Value);
}

void APlayerCharacter::BeginCrouch()
{
	Crouch();
}

void APlayerCharacter::EndCrouch()
{
	UnCrouch();
}

void APlayerCharacter::BeginSprint()
{
	if (!CharacterMovementComp)
	{
		return;
	}

	CharacterMovementComp->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::EndSprint()
{
	if (!CharacterMovementComp)
	{
		return;
	}

	CharacterMovementComp->MaxWalkSpeed = DefaultSpeed;
}

void APlayerCharacter::DestroySelf()
{
	Destroy();
	APlatformerGameModeBase* GameMode = Cast<APlatformerGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->DeathCount++;
		GameMode->Respawn();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::EndSprint);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::EndCrouch);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= Damage;
	if (Health <= 0.0f)
	{
		DestroySelf();
	}
	return Health;
}

