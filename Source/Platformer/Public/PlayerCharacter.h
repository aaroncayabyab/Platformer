// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;

UCLASS()
class PLATFORMER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void EndCrouch();

	void BeginSprint();

	void EndSprint();

	void DestroySelf();

	UCharacterMovementComponent* CharacterMovementComp;

	UPROPERTY(EditAnywhere, Category = "Platformer")
		float SprintSpeed;

	UPROPERTY(EditAnywhere, Category = "Platformer")
		float DefaultSpeed;

	UPROPERTY(EditAnywhere, Category = "Platformer")
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platformer")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platformer")
		USpringArmComponent* SpringArmComp;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
