// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "TileState.h"
#include "UnitData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FUnitData
{
	GENERATED_USTRUCT_BODY()

public:
	FUnitData();
	FUnitData(FString Name, FString Team, int Health);

	int Health;
	int MaxHealth;
	int Speed;
	int Attack;
	
	FString Name;
	FString Team;

	void SetHealth(float const value);

};
