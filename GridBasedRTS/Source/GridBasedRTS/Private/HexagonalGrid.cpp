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

	GenerateGrid(true);

	height = 4;
	width = 4;
	TileSize = 170.f;
	SetRootComponent(InstancedStaticMeshComponent);
}

void AHexagonalGrid::SetGridParameters(float NewMapSize, float NewTileSize) {
	MapSize = NewMapSize;
	TileSize = NewTileSize;
}

bool AHexagonalGrid::IsHoveringTile(FVector HitLocation) {

	return true;
}

// Generates Map Tiles
void AHexagonalGrid::GenerateGrid(bool isHexagonal)
{


	float size = 100.f;

	InstancedStaticMeshComponent->ClearInstances();
	TileDataMap.Reset();

	//TileSize = GridInfo;
	// Radius from center to edge = 173.2
	// Radius from center to corner = 75
	//
	if (isHexagonal) {
		for (int x = -MapSize; x <= MapSize; x++) {
			for (int y = -MapSize; y <= MapSize; y++){
				AddTile(x,y);
			}
		}
	}
	else {
		float horiz = 3.f / 2.f * size / 2;
		float vert = sqrt(3) * size / 2;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				float x = size * sqrt(3) * (j + (i % 1) / 2.f);
				float y = size * 1.5 * i;
				if (i % 2 == 1) {
					x -= (size * sqrt(3) / 2);
				}
				FTransform transform(FRotator(0.f, 90.f, 0.f), FVector(y, x, 0.1f), FVector(1.f, 1.f, 1.f));
				TileDataMap.Add(FVector(x, y, 0),FTileData(FVector(i, j, 0), transform));
				InstancedStaticMeshComponent->AddInstance(transform);
			}
		}
	}



}

void AHexagonalGrid::IncreaseOffsetAdjust() {
	//OffsetAdjust += 1.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(OffsetAdjust,2));
}

void AHexagonalGrid::AddTile(float x, float y) {
	float Offset = ((int)x % 2 == 0) ? 0.f : TileSize / 2.0f;
	FTransform transform(FRotator(0.f, 90.f, 0.f), FVector((x* TileSize) -(x*TileSize/10.f), y*TileSize+Offset, 0.1f), FVector(1.f, 1.f, 1.f));

	TileDataMap.Add(FVector(x, y, 0),FTileData(FVector(x, y, 0), transform));
	InstancedStaticMeshComponent->AddInstance(transform);

}

// Called when the game starts or when spawned
void AHexagonalGrid::BeginPlay()
{
	Super::BeginPlay();
	GenerateGrid(true);
}

// Called every frame
void AHexagonalGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

