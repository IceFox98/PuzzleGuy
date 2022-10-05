// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBlocker.generated.h"


UCLASS()
class ESCAPEGAME_API APlayerBlocker : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerBlocker();

public:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

private:

	/** The current Angle of the movement */
	float Angle;

	/** The max angle the movement can reach */
	float MaxAngle;

	/** Is something ovelapping the Box? */
	bool bOverlapping;

	/** The starting offset of the Mesh, relative to the Root component */
	FVector InitialMeshOffset;

public:

	/** How fast the block should move */
	float AnglePerSeconds;

	/** How much the block should move */
	FVector MovementAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveBlockTick(float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
