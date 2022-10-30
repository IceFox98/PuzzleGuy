// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactives/ActorTriggerer.h"
#include "Interactives/Triggerable.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "PuzzleGuyUtils.h"

// Sets default values
AActorTriggerer::AActorTriggerer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorTriggerer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorTriggerer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorTriggerer::TriggerActors()
{
	for (AActor* ActorToTrigger : ActorsToTrigger)
	{
		//if (ITriggerable* Triggerable = Cast<ITriggerable>(ActorToTrigger))
		if (ActorToTrigger->Implements<UTriggerable>())
		{
			//Cast<ITriggerable>(ActorToTrigger)->Trigger();
			ITriggerable* Triggerable = Cast<ITriggerable>(ActorToTrigger);
			Triggerable->Execute_Trigger(ActorToTrigger);
		}
		else
		{
			SCREEN_LOG(5.f, FColor::Red, "Actor is not Triggerable!");
		}
	}

}

void AActorTriggerer::SendMessage(const FSampleMessage& InMessage)
{
	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(TAG_Sample_Channel, InMessage);
}

