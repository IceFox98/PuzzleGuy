// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HideHandler.h"
#include "Characters/PlayerCharacter.h"

// Sets default values for this component's properties
UHideHandler::UHideHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHideHandler::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = Cast<ACharacterBase>(GetOwner());
}


// Called every frame
void UHideHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bWantToHide)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Dist(CharacterRef->GetActorLocation(), HideStartPos));

		if (!CharacterRef->bIsCrouched)
		{
			if (FVector::Dist(CharacterRef->GetActorLocation(), HideStartPos) > 0.5f)
			{
				FVector NewPosition = FMath::VInterpConstantTo(CharacterRef->GetActorLocation(), HideStartPos, DeltaTime, 300.f);
				CharacterRef->SetActorLocation(NewPosition);
				return;
			}
		}

		CharacterRef->Crouch();

		if (FVector::Dist(CharacterRef->GetActorLocation(), HideEndPos) > 0.5f)
		{
			FVector NewPosition = FMath::VInterpConstantTo(CharacterRef->GetActorLocation(), HideEndPos, DeltaTime, 300.f);
			CharacterRef->SetActorLocation(NewPosition);
			return;
		}

		bWantToHide = false;
		bIsHidden = true;
	}
}

void UHideHandler::ManageHiding(const FVector& StartPos, const FVector& EndPos)
{
	if (!CharacterRef) return;

	if (!bIsHidden)
	{
		UE_LOG(LogTemp, Warning, TEXT("ManageHiding"));

		HideStartPos = StartPos;
		HideStartPos.Z = CharacterRef->GetActorLocation().Z;
		HideEndPos = EndPos;
		HideEndPos.Z = CharacterRef->GetActorLocation().Z;
		bWantToHide = true;

	}

}

