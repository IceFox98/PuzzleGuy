// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "AbilitySystem/PuzzleGuyAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/PuzzleGuyAttributeSet.h"
#include "AbilitySystem/Abilities/PuzzleGuyGameplayAbility.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bAbilitiesInitialized = false;

	// Create a follow camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	ThrowStartingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ThrowStartingPoint"));
	ThrowStartingPoint->SetupAttachment(RootComponent);

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<UPuzzleGuyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);
	//AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UPuzzleGuyAttributeSet>(TEXT("Attributes"));


	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanJump = true;

	ThrowForce = 1200.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initializes the GAS Actor on the server
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();


	if (AbilitySystemComponent && InputComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"EPuzzleGuyAbilityInputID",
			static_cast<int32>(EPuzzleGuyAbilityInputID::Confirm),
			static_cast<int32>(EPuzzleGuyAbilityInputID::Cancel)
		);

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);

	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);


	if (AbilitySystemComponent && InputComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"EPuzzleGuyAbilityInputID",
			static_cast<int32>(EPuzzleGuyAbilityInputID::Confirm),
			static_cast<int32>(EPuzzleGuyAbilityInputID::Cancel)
		);

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);

	}

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	//PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("ThrowObject"), IE_Pressed, this, &APlayerCharacter::ThrowObject);

}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerCharacter::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if (HasAuthority() && !bAbilitiesInitialized)
	{
		// Grant abilities, but only on the server

		for (TSubclassOf<UPuzzleGuyGameplayAbility>& StartupAbility : Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				StartupAbility,
				1,
				static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),
				this
			));
		}

		// Now apply passives: set default values to Effects
		for (const TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);

			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*NewHandle.Data.Get(),
					AbilitySystemComponent
				);
			}
		}

		bAbilitiesInitialized = true;
	}
}

//void APlayerCharacter::OnHealthChanged(UHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
//{
//	Super::OnHealthChanged(OwningHealthComp, Health, HealthDelta, DamageType, InstigatedBy, DamageCauser);
//
//	if (HealthComp->IsDead())
//	{
//		UE_LOG(LogTemp, Warning, TEXT("You're dead!"));
//		return;
//	}
//
//	// Do other stuff
//}

void APlayerCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnHealthChanged(DeltaValue, EventTags);
	}
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

void APlayerCharacter::ThrowObject()
{
	if (InventoryComponent && ThrowStartingPoint)
	{
		AInventoryItem* ActorToThrow = InventoryComponent->DropSelectedItem();

		if (!ActorToThrow) return;

		if (ActorToThrow->IsThrowable())
		{
			// Set Object location to throwing point location, before throwing it
			ActorToThrow->SetActorLocation(ThrowStartingPoint->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);

			ActorToThrow->BaseMesh->SetSimulatePhysics(true);
			FVector Location;
			FRotator Rotation;
			GetActorEyesViewPoint(Location, Rotation);
			ActorToThrow->BaseMesh->SetAllPhysicsLinearVelocity(Rotation.Vector() * ThrowForce);
		}
	}
}
