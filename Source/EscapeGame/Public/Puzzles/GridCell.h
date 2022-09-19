// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactives/Interactable.h"
#include "GridCell.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractSignature, int32, Position);

UENUM()
enum ECellColor
{
	BeginFocus,
	EndFocus,
	Guessed
};

UCLASS()
class ESCAPEGAME_API AGridCell : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridCell();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		FLinearColor BaseColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		FLinearColor InteractColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		FLinearColor GuessedColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool Locked;

public:

	FOnInteractSignature OnInteractDelegate;

private:

	int32 Position;

	UPROPERTY()
		UMaterialInstanceDynamic* MatInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void Initialize(class AMemoryGrid* Grid);

	void Initialize(int32 m_Position);

	virtual void OnInteract_Implementation(class AController* Controller, UActorComponent* Comp) override;

	UFUNCTION(BlueprintCallable)
		void ChangeColor(ECellColor SelectColor);

};
