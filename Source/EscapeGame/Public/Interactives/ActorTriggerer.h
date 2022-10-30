// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "ActorTriggerer.generated.h"

USTRUCT(BlueprintType)
struct FSampleMessage
{
public:

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MyString;
};


UCLASS()
class ESCAPEGAME_API AActorTriggerer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorTriggerer();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Triggerer")
		TArray<AActor*> ActorsToTrigger;

	UPROPERTY(EditAnywhere, Category = "Triggerer")
		FGameplayTag TAG_Sample_Channel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void TriggerActors();

	UFUNCTION(BlueprintCallable)
	void SendMessage(const FSampleMessage& InMessage);

};
