// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "TileState.h"
#include "Engine/DataTable.h"
#include "UnitData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FUnitData();
	FUnitData(FString Name, FString Team, int Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team Data")
	int MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team Data")
	FString Team;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team Data")
	FColor TeamColor;

	int Health;
	int Speed;
	int Attack;
	
	FString Name;


	void SetHealth(float const value);

};
