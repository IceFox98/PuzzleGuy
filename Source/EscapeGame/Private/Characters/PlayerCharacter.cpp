// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a follow camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	//GetMovementComponent()->GetNavAgentPropertiesRef().bCanJump = true;

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::Interact);

}

void APlayerCharacter::OnHealthChanged(UHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnHealthChanged(OwningHealthComp, Health, HealthDelta, DamageType, InstigatedBy, DamageCauser);

	if (HealthComp->IsDead())
	{
		UE_LOG(LogTemp, Warning, TEXT("You're dead!"));
		return;
	}

	// Do other stuff
}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void APlayerCharacter::Interact()
{
	if (InteractionComponent)
	{
		FInteractionData ObjData = InteractionComponent->FindInteractiveObject();

		if (ObjData.IsInteractive)
		{
			IInteractable* InteractiveObj = Cast<IInteractable>(ObjData.HitActor);
			InteractiveObj->Execute_OnInteract(ObjData.HitActor, GetController(), ObjData.HitComponent);
		}
	}
}