// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PuzzleGuyUtils.generated.h"

#define CONSOLE_LOG(LogType, text, ...) UE_LOG(LogTemp, LogType, TEXT("%s -> %s"), ANSI_TO_TCHAR(__FUNCTION__),  *FString::Printf(TEXT(text), ##__VA_ARGS__))

#define SCREEN_LOG(TimeToDisplay, Color, Text, ...) GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, FString::Printf(TEXT(Text), ##__VA_ARGS__))

UCLASS(BlueprintType)
class ESCAPEGAME_API UPuzzleGuyUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

};

