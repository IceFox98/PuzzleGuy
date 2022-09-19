// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactives/Furniture.h"
#include "Characters/PlayerCharacter.h"
#include "Curves/CurveFloat.h"
//#include "Components/InputComponent.h"
//#include "InputCoreTypes.h"


// Sets default values
AFurniture::AFurniture()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DrawersData.OpeningSpeed = 4.f;
	DrawersData.ClosingSpeed = 3.f;

	CabinetDoorsData.OpeningSpeed = 4.f;
	CabinetDoorsData.ClosingSpeed = 3.f;

	DrawerSetupIndex = 0;
	CabinetDoorSetupIndex = 0;

}

// Called when the game starts or when spawned
void AFurniture::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFurniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageDrawers(DeltaTime);
	ManageCabinetDoors(DeltaTime);

}

void AFurniture::OnInteract_Implementation(class AController* Controller, UActorComponent* Comp)
{
	// Search for Drawer
	int32 CompIndex = FindDrawerIndexByComponent(Comp);

	if (CompIndex != -1) // Drawer found
	{
		if (CanOpenDrawer(CompIndex, Controller))
		{
			// Switch state
			Drawers[CompIndex].State = static_cast<EState>(1 - Drawers[CompIndex].State);

			DrawersToUpdate.AddUnique(CompIndex);
		}

		return;
	}

	// Search for Cabinet Door
	CompIndex = FindCabinetDoorIndexByComponent(Comp);

	if (CompIndex != -1) // Cabinet Door found
	{
		if (CanOpenCabinetDoor(CompIndex, Controller))
		{
			// Switch state
			CabinetDoors[CompIndex].State = static_cast<EState>(1 - CabinetDoors[CompIndex].State);

			CabinetDoorsToUpdate.AddUnique(CompIndex);
		}

		return;
	}

}

int AFurniture::FindDrawerIndexByComponent(UActorComponent* Comp) const
{
	for (int i = 0; i < Drawers.Num(); i++)
	{
		FDrawer CurrDrawer = Drawers[i];

		if (CurrDrawer.Component == Comp)
		{
			return i;
		}
	}

	return -1;
}

int AFurniture::FindCabinetDoorIndexByComponent(UActorComponent* Comp) const
{
	for (int i = 0; i < CabinetDoors.Num(); i++)
	{
		FCabinetDoor CurrCD = CabinetDoors[i];

		if (CurrCD.Component == Comp)
		{
			return i;
		}
	}

	return -1;
}

bool AFurniture::CanOpenDrawer(const int32 DrawerIndex, class AController* mInstigator)
{
	if (DrawerIndex >= Drawers.Num()) return false;

	FDrawer CurrDrawer = Drawers[DrawerIndex];

	if (CurrDrawer.IsLocked)
	{
		return CheckPlayerForKey(CurrDrawer.KeyID, mInstigator);
	}

	return true;
}

bool AFurniture::CanOpenCabinetDoor(const int32 CabinetDoorIndex, class AController* mInstigator)
{
	if (CabinetDoorIndex >= CabinetDoors.Num()) return false;

	FCabinetDoor CurrCD = CabinetDoors[CabinetDoorIndex];

	if (CurrCD.IsLocked)
	{
		return CheckPlayerForKey(CurrCD.KeyID, mInstigator);
	}

	return true;
}

void AFurniture::SetupDrawer(USceneComponent* DrawerComp, float MaxOpeningLength)
{
	if (!DrawerComp) return;

	if (UPrimitiveComponent* Comp = Cast<UPrimitiveComponent>(DrawerComp)) // Ignore Player
	{
		Comp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}

	FDrawer NewDrawer;
	NewDrawer.Component = DrawerComp;
	NewDrawer.MaxOpeningLength = MaxOpeningLength;

	if (DrawerSetupIndex < DrawersSetup.Num()) // If it has at least 1 drawer setup
	{
		FDrawerSetup& DrawerSetup = DrawersSetup[DrawerSetupIndex++];
		NewDrawer.KeyID = DrawerSetup.KeyID;
		NewDrawer.IsLocked = DrawerSetup.IsLocked;
		NewDrawer.State = DrawerSetup.State;

		for (int8 i = 0; i < DrawerSetup.Content.Num(); i++)
		{
			AActor* ContentActor = DrawerSetup.Content[i];

			if (ContentActor)
			{
				ContentActor->AttachToComponent(DrawerComp, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}

	Drawers.Add(NewDrawer);
}

void AFurniture::SetupCabinetDoor(USceneComponent* CabinetDoorComp, float MaxOpeningAngle, EDirection OpeningAxis)
{
	if (!CabinetDoorComp) return;

	if (OpeningAxis > EDirection::Z) // Then is negative
	{
		MaxOpeningAngle *= -1;
	}

	if (UPrimitiveComponent* Comp = Cast<UPrimitiveComponent>(CabinetDoorComp)) // Ignore Player
	{
		Comp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}

	FCabinetDoor NewCD;
	NewCD.Component = CabinetDoorComp;
	NewCD.MaxOpeningAngle = MaxOpeningAngle;

	if (DrawerSetupIndex < CabinetDoorsSetup.Num()) // If it has at least 1 cabinet door setup
	{
		FCabinetDoorSetup& CabinetDoorSetup = CabinetDoorsSetup[CabinetDoorSetupIndex++];
		NewCD.KeyID = CabinetDoorSetup.KeyID;
		NewCD.IsLocked = CabinetDoorSetup.IsLocked;
		NewCD.State = CabinetDoorSetup.State;
	}

	CabinetDoors.Add(NewCD);
}

void AFurniture::ManageDrawers(float DeltaTime)
{
	if (!DrawersData.OpenCloseCurve)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Open-Close Curve missing!"));
		return;
	}

	for (int i = 0; i < DrawersToUpdate.Num(); i++)
	{
		int32 DrawerIndex = DrawersToUpdate[i];
		FDrawer& CurrDrawer = Drawers[DrawerIndex]; // Note: It's important here to get the reference and not a copy

		//UE_LOG(LogTemp, Warning, TEXT("test"));

		float TargetSpeed = 0.f;

		switch (CurrDrawer.State)
		{
		case EState::Opened: // The drawer has just been opened (so it's opening right now)
			TargetSpeed = DrawersData.OpeningSpeed;
			break;

		case EState::Closed:
			TargetSpeed = DrawersData.ClosingSpeed * -1;
			break;
		}

		// Calculate the new time of the opening curve, depending on the speed
		float NewAnimTime = (TargetSpeed * DeltaTime) + CurrDrawer.CurrAnimTime;
		NewAnimTime = FMath::Clamp(NewAnimTime, 0.f, 1.f);

		CurrDrawer.CurrAnimTime = NewAnimTime;

		// We use the curve to determine how much the drawer has to move
		float CurveValue = DrawersData.OpenCloseCurve->GetFloatValue(NewAnimTime);

		// Multiply that value for the opening length (or the size of the drawer) and then we add the eventual starting position 
		float NewLocationY = (CurveValue * CurrDrawer.MaxOpeningLength) + CurrDrawer.StartPosition.Y;
		FVector CurrLocation = CurrDrawer.Component->GetRelativeLocation();

		// Interpolate the final value to get more smoothness
		NewLocationY = FMath::FInterpTo(CurrLocation.Y, NewLocationY, DeltaTime, 10.f);

		CurrDrawer.Component->SetRelativeLocation(FVector(CurrLocation.X, NewLocationY, CurrLocation.Z));

		// Remove the drawer when is reaches the final location
		if (FMath::IsNearlyEqual(NewLocationY, CurrDrawer.MaxOpeningLength, 0.0001f))
		{
			DrawersToUpdate.RemoveAt(i);
		}
	}
}

void AFurniture::ManageCabinetDoors(float DeltaTime)
{
	if (!CabinetDoorsData.OpenCloseCurve)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Open-Close Curve missing!"));
		return;
	}

	for (int i = 0; i < CabinetDoorsToUpdate.Num(); i++)
	{
		int32 CabinetDoorIndex = CabinetDoorsToUpdate[i];
		FCabinetDoor& CurrCabinetDoor = CabinetDoors[CabinetDoorIndex]; // Note: It's important here to get the reference and not a copy

		//UE_LOG(LogTemp, Warning, TEXT("test"));

		float TargetSpeed = 0.f;

		switch (CurrCabinetDoor.State)
		{
		case EState::Opened: // The cabinet door has just been opened (so it's opening right now)
			TargetSpeed = CabinetDoorsData.OpeningSpeed;
			break;

		case EState::Closed:
			TargetSpeed = CabinetDoorsData.ClosingSpeed * -1;
			break;
		}

		// Calculate the new time of the opening curve, depending on the speed
		float NewAnimTime = (TargetSpeed * DeltaTime) + CurrCabinetDoor.CurrAnimTime;
		NewAnimTime = FMath::Clamp(NewAnimTime, 0.f, 1.f);

		CurrCabinetDoor.CurrAnimTime = NewAnimTime;

		// We use the curve to determine how much the cabinet door has to move
		float CurveValue = CabinetDoorsData.OpenCloseCurve->GetFloatValue(NewAnimTime);

		// Multiply that value for the opening angle and then we add the eventual starting rotation 
		float NewYaw = (CurveValue * CurrCabinetDoor.MaxOpeningAngle) + CurrCabinetDoor.StartRotation.Yaw;
		FRotator CurrRotation = CurrCabinetDoor.Component->GetRelativeRotation();

		// Interpolate the final value to get more smoothness
		NewYaw = FMath::FInterpTo(CurrRotation.Yaw, NewYaw, DeltaTime, 10.f);

		CurrCabinetDoor.Component->SetRelativeRotation(FRotator(CurrRotation.Pitch, NewYaw, CurrRotation.Roll));

		// Remove the cabinet door when is reaches the final location
		if (FMath::IsNearlyEqual(NewYaw, CurrCabinetDoor.MaxOpeningAngle, 0.0001f))
		{
			CabinetDoorsToUpdate.RemoveAt(i);
		}
	}
}

bool AFurniture::CheckPlayerForKey(const FGuid KeyID, class AController* mInstigator) const
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(mInstigator->GetPawn());

	if (Player)
		return Player->HasKey(KeyID); // Implemented via Blueprint

	return false;
}