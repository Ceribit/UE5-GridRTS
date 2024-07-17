// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonalGrid.h"
#include <algorithm>

// Sets default values
AHexagonalGrid::AHexagonalGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	InstancedStaticMeshComponent->SetMobility(EComponentMobility::Movable);
	InstancedStaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Block);
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

FIntPoint AxialRound(float x, float y) {
	const int xgrid = std::round(x), ygrid = std::round(y);
	x -= xgrid;
	y -= ygrid;
	if (std::abs(x) >= std::abs(y)) {
		return FIntPoint(xgrid + round(x + 0.5 * y), ygrid);
	}
	else {
		return FIntPoint(xgrid, ygrid + round(y + 0.5 * x));
	}
}

// TODO: Convert into a utility library
FIntPoint hexToFlatCoordinates(FVector hex)
{
	FIntPoint coordinates;
	coordinates.X = hex.X;
	coordinates.Y = hex.Z;
	return coordinates;
}

// TODO: Convert into a utility library
FIntPoint axialToOffsetCoordinates(FIntPoint axial)
{
	FIntPoint offset;
	offset.X = axial.X;
	offset.Y = axial.Y + ceilf((float)axial.X / 2.0);
	return offset;
}

FIntPoint AHexagonalGrid::GetTileIndexFromMousePosition(FVector HitLocation) {
	float radius = TILE_SIZE * TileScale;
	float a = HitLocation.X;
	float b = HitLocation.Y;

	float x = 2.0 / 3.0 * a / radius;
	float z = (1.0 / 3.0 * sqrt(3.0) * b - 1.0 / 3.0 * a) / radius;
	float y = -x - z;

	int ix = (int)round((floor(x - y) - floor(z - x)) / 3.0);
	int iy = (int)round((floor(y - z) - floor(x - y)) / 3.0);
	int iz = (int)round((floor(z - x) - floor(y - z)) / 3.0);

	FIntPoint Corrected = hexToFlatCoordinates(FVector(ix, iy, iz));
	//Corrected.X -= 1;
	return axialToOffsetCoordinates(Corrected);
}

TMap<FIntPoint, FTileData> AHexagonalGrid::GetTileDataMap() {
	return TileDataMap;
}

// Generates Map Tiles
void AHexagonalGrid::GenerateGrid()
{
	InstancedStaticMeshComponent->ClearInstances();
	TileDataMap.Reset();

	for (int q = -MapSize; q <= MapSize; q++) {
		int r1 = std::max(-MapSize, -q - MapSize);
		int r2 = std::min(MapSize, -q + MapSize);

		for (int r = r1; r <= r2; r++) {
			// Convert RadialCoord to Offset
			FIntPoint Index = AxialToOffset(q, r);
			AddTile(Index);

		}
	}
	//for (int x = -MapSize; x <= MapSize; x++) {
	//	for (int y = -MapSize; y <= MapSize; y++){
	//		AddTile(x,y);
	//	}

}

FIntPoint AHexagonalGrid::AxialToOffset(int q, int r) {
	int x = q;
	int y = r + (q + (q % 2 == 1)) / 2;
	return FIntPoint(x, y);
}

FVector AHexagonalGrid::OffsetToAxial(FIntPoint Index) {
	return FVector(0, 0, 0);
}

// Even-Q
void AHexagonalGrid::AddTile(FIntPoint Index) {
	int x = Index[0];
	int y = Index[1];
	float Offset = ((int)x % 2 == 0) ? 0.f : TileScale * TILE_SIZE * sqrt(3)/2;
	FTransform transform(FRotator(0.f, 90.f, 0.f), FVector(TileScale * TILE_SIZE * x * 1.5, TileScale* TILE_SIZE * y * sqrt(3)-Offset, 0.1f), FVector(TileScale, TileScale, 1.f));
	TileDataMap.Add(FIntPoint(x, y),FTileData(FIntPoint(x, y), transform));
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

