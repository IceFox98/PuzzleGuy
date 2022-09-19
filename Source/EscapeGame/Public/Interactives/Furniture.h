// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactives/Interactable.h"
#include "Misc/Guid.h"
#include "Furniture.generated.h"


//Evento OnInteracted (success or not)


UENUM()
enum EDirection
{
	X, Y, Z,
	NX, NY, NZ // The negative ones
};

UENUM()
enum EState
{
	Opened,
	Closed
};

USTRUCT(BlueprintType)
struct FFurnitureData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere)
		float OpeningSpeed;

	UPROPERTY(EditAnywhere)
		float ClosingSpeed;

	UPROPERTY(EditDefaultsOnly)
		class UCurveFloat* OpenCloseCurve;

};

USTRUCT(BlueprintType)
struct FDrawerSetup
{
	GENERATED_USTRUCT_BODY()

public:
	FDrawerSetup() :
		State(EState::Closed), IsLocked(false)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EState> State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FGuid KeyID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<AActor*> Content;
};

USTRUCT(BlueprintType)
struct FDrawer
{
	GENERATED_USTRUCT_BODY()

public:
	FDrawer() :
		IsLocked(false), State(EState::Closed), StartPosition(FVector::ZeroVector), CurrAnimTime(0), MaxOpeningLength(0)
	{}

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Component;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsLocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TEnumAsByte<EState> State;

	UPROPERTY(VisibleAnywhere)
		FGuid KeyID;

	UPROPERTY(VisibleAnywhere)
		FVector StartPosition;

	UPROPERTY(VisibleAnywhere)
		float CurrAnimTime;

	UPROPERTY(VisibleAnywhere)
		float MaxOpeningLength;
};

USTRUCT(BlueprintType)
struct FCabinetDoorSetup
{
	GENERATED_USTRUCT_BODY()

public:
	FCabinetDoorSetup() :
		State(EState::Closed), IsLocked(false)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EState> State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FGuid KeyID;
};

USTRUCT(BlueprintType)
struct FCabinetDoor
{
	GENERATED_USTRUCT_BODY()

public:
	FCabinetDoor() :
		IsLocked(false), State(EState::Closed), StartRotation(FRotator::ZeroRotator), CurrAnimTime(0), MaxOpeningAngle(0)
	{}

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Component;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsLocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TEnumAsByte<EState> State;

	UPROPERTY(VisibleAnywhere)
		FGuid KeyID;

	UPROPERTY(VisibleAnywhere)
		FRotator StartRotation;

	UPROPERTY(VisibleAnywhere)
		float CurrAnimTime;

	UPROPERTY(VisibleAnywhere)
		float MaxOpeningAngle;
};

UCLASS()
class ESCAPEGAME_API AFurniture : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFurniture();


protected:

	/* Drawers */
	UPROPERTY(BlueprintReadOnly, Category = "Drawers")
		TArray<FDrawer> Drawers;

	UPROPERTY(EditAnywhere, Category = "Drawers")
		TArray<FDrawerSetup> DrawersSetup;

	UPROPERTY(EditAnywhere, Category = "Drawers")
		FFurnitureData DrawersData;

	/* Cabinet Doors*/
	UPROPERTY(BlueprintReadOnly, Category = "Cabinet Doors")
		TArray<FCabinetDoor> CabinetDoors;

	UPROPERTY(EditAnywhere, Category = "Cabinet Doors")
		TArray<FCabinetDoorSetup> CabinetDoorsSetup;

	UPROPERTY(EditAnywhere, Category = "Cabinet Doors")
		FFurnitureData CabinetDoorsData;

private:

	UPROPERTY()
		TArray<int32> DrawersToUpdate;

	int32 DrawerSetupIndex;

	UPROPERTY()
		TArray<int32> CabinetDoorsToUpdate;

	int32 CabinetDoorSetupIndex;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation(class AController* Controller, UActorComponent* Comp) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CheckPlayerForKey(const FGuid KeyID, class AController* mInstigator) const;

	UFUNCTION(BlueprintCallable)
		void SetupDrawer(USceneComponent* DrawerComp, float MaxOpeningLength);

	UFUNCTION(BlueprintCallable)
		int FindDrawerIndexByComponent(UActorComponent* Comp) const;

	UFUNCTION(BlueprintCallable)
		void SetupCabinetDoor(USceneComponent* CabinetDoorComp, float MaxOpeningAngle, EDirection OpeningAxis);

	UFUNCTION(BlueprintCallable)
		int FindCabinetDoorIndexByComponent(UActorComponent* Comp) const;

private:

	bool CanOpenDrawer(const int32 DrawerIndex, class AController* mInstigator);

	void ManageDrawers(float DeltaTime);

	bool CanOpenCabinetDoor(const int32 CabinetDoorIndex, class AController* mInstigator);

	void ManageCabinetDoors(float DeltaTime);


};
