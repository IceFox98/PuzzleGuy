// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HideHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UHideHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHideHandler();

protected:

	UPROPERTY()
		class ACharacterBase* CharacterRef;

	bool bWantToHide;

	bool bWantToExit;

	FVector HideStartPos;
	FVector HideEndPos;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ManageHiding(const FVector& StartPos, const FVector& EndPos);

	bool bIsHidden;
};
