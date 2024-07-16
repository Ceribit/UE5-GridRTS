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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AHexagonalGrid();

	UFUNCTION(BlueprintCallable)
	void GenerateGrid();

	UFUNCTION(BlueprintCallable)
	void SetGridParameters(float NewMapSize, float NewTileSize);

	UFUNCTION(BlueprintCallable)
	FIntPoint GetTileIndexFromMousePosition(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	TMap<FIntPoint, FTileData> GetTileDataMap();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int height;
	int width;
	int MapSize = 1;
	const float TILE_SIZE = 100.f;
	float TileScale = 1.f;

	TMap<FIntPoint,FTileData> TileDataMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;


public:
	void AddTile(FIntPoint Index);
	FVector OffsetToAxial(FIntPoint index);
	FIntPoint AxialToOffset(int q, int r);


};
