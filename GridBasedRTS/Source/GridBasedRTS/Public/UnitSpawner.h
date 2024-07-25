// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexagonalGrid.h"
#include "DefaultCharacter.h"
#include "Engine/DataTable.h"
#include "UnitSpawner.generated.h"

UCLASS()
class GRIDBASEDRTS_API AUnitSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FIntPoint SpawnLocation;
	
	AHexagonalGrid* Grid;

	UDataTable* DataTable;

	UFUNCTION(BlueprintCallable)
	void CreateUnit();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Class")
	TSubclassOf<ADefaultCharacter> UnitClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SetGrid(AHexagonalGrid* Grid);
	
	UFUNCTION(BlueprintCallable)
	void SetUnitSpawnLocation(FIntPoint Index);
};
