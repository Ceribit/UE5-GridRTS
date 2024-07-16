// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonalGrid.h"

// Sets default values
AHexagonalGrid::AHexagonalGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	InstancedStaticMeshComponent->SetMobility(EComponentMobility::Movable);
	InstancedStaticMeshComponent->SetCollisionProfileName("WalkableGround");
	//InstancedStaticMeshComponent->SetStaticMesh(StaticMesh.object);
	//GridInfo = FVector(MapSize, TileSize, 0.f);

	TileScale = 1.f;
	GenerateGrid();

	height = 4;
	width = 4;
	SetRootComponent(InstancedStaticMeshComponent);
}

void AHexagonalGrid::SetGridParameters(float NewMapSize, float NewTileScale) {
	MapSize = NewMapSize;
	TileScale = NewTileScale;
}

bool AHexagonalGrid::IsHoveringTile(FVector HitLocation) {
	return true;
}

TMap<FVector, FTileData> AHexagonalGrid::GetTileDataMap() {
	return TileDataMap;
}

// Generates Map Tiles
void AHexagonalGrid::GenerateGrid()
{
	InstancedStaticMeshComponent->ClearInstances();
	TileDataMap.Reset();

	for (int x = -MapSize; x <= MapSize; x++) {
		for (int y = -MapSize; y <= MapSize; y++){
			AddTile(x,y);
		}
	}




}

void AHexagonalGrid::AddTile(int x, int y) {
	float Offset = ((int)x % 2 == 0) ? 0.f : TileScale * TILE_SIZE * sqrt(3)/2;
	FTransform transform(FRotator(0.f, 90.f, 0.f), FVector(TileScale * TILE_SIZE * x * 1.5, TileScale* TILE_SIZE * y * sqrt(3)+Offset, 0.1f), FVector(TileScale, TileScale, 1.f));
	// relative_location_x = x * tileSize - (x * tileSize / 10) = 0.9 * x *tileSize -> x = relative_location / 0.9 / tileSize
	// relative_location_x = y*TileSize+Offset

	TileDataMap.Add(FVector(x, y, 0),FTileData(FVector(x, y, 0), transform));
	InstancedStaticMeshComponent->AddInstance(transform);

}

// Called when the game starts or when spawned
void AHexagonalGrid::BeginPlay()
{
	Super::BeginPlay();
	GenerateGrid();
}

// Called every frame
void AHexagonalGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

