// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "TileState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class UTileState
{
	NONE = 0 UMETA(DiplsayName = "None"),
	SELECTED = 1 UMETA(DisplayName = "Selected"),
	OBSTACLE = 2 UMETA(DisplayName = "Obstacle"),
};
