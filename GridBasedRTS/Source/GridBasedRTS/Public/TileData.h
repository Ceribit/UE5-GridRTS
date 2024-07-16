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
	GENERATED_USTRUCT_BODY()

public:
	FTileData() {}
	FTileData(FIntPoint NewIndex, FTransform NewTransform);

	UTileState TileState;

	UPROPERTY(BlueprintReadWrite)
	FIntPoint Index;

	UPROPERTY(BlueprintReadWrite)
	FVector AxialCoord;

	UPROPERTY(BlueprintReadWrite)
	FTransform Transform;

};
