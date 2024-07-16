// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Engine/Classes/Components/InstancedStaticMeshComponent.h" 
#include "Kismet/KismetMathLibrary.h"
#include "TileData.h"
#include "HexagonalGrid.generated.h"

UCLASS()
class GRIDBASEDRTS_API AHexagonalGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexagonalGrid();

	UFUNCTION(BlueprintCallable)
	void GenerateGrid();

	UFUNCTION(BlueprintCallable)
	void SetGridParameters(float NewMapSize, float NewTileSize);

	UFUNCTION(BlueprintCallable)
	bool IsHoveringTile(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	TMap<FVector, FTileData> GetTileDataMap();

	void AddTile(int x, int y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int height;
	int width;
	int MapSize = 1;
	const float TILE_SIZE = 100.f;
	float TileScale = 1.f;

	TMap<FVector,FTileData> TileDataMap;

	// MapSize, TileSize
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	//FVector<float> GridInfo(0.f,0.f,0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	//UStaticMeshComponent* StaticMesh;
};
