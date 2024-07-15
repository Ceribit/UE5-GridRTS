// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "TileState.h"
#include "TileData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTileData
{
	GENERATED_BODY()

public:
	FTileData() {}
	FTileData(FVector NewIndex, FTransform NewTransform);

	UTileState TileState;
	FVector Index;
	FTransform Transform;

};
