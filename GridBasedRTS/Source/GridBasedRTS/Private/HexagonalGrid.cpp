// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonalGrid.h"

// Sets default values
AHexagonalGrid::AHexagonalGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	InstancedStaticMeshComponent->SetMobility(EComponentMobility::Movable);
	InstancedStaticMeshComponent->SetCollisionProfileName("BlockAll");
	//InstancedStaticMeshComponent->SetStaticMesh(StaticMesh.object);
	height = 4;
	width = 4;
	float size = 200.f / 2.f;
	float horiz = 3.f / 2.f * size / 2;
	float vert = sqrt(3) * size / 2;
	// Radius from center to edge = 173.2
	// Radius from center to corner = 75
	//
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			float x = size * sqrt(3) * (j + (i % 1) / 2.f);
			float y = size * 1.5 * i;
			if (i % 2 == 1) {
				x -= (size * sqrt(3) / 2);
			}
			FTransform transform(FRotator(0.f, 90.f, 0.f), FVector(y,x,0.1f), FVector(1.f,1.f,1.f));
			tileData.Add(FVector2D(i, j), transform);
			InstancedStaticMeshComponent->AddInstance(transform);
		}
	}

	
	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < height; j++) {
	//		for (int k = 0; k < height; k++) {
	//			FTransform transform(FRotator(0.f, 90.f, 0.f), FVector(size*(i * sqrt(3.f) + sqrt(3.f)/2.f * k), size*(3.f/2.f * k), 0.1f), FVector(1.f, 1.f, 1.f));
	//			tileData.Add(FVector(i, j, k), transform);
	//			InstancedStaticMeshComponent->AddInstance(transform);
	//		}
	//	}
	//}
	
	SetRootComponent(InstancedStaticMeshComponent);
}

// Called when the game starts or when spawned
void AHexagonalGrid::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			//for (int k = 0; k < 2; k++) {
			//	FTransform* transform = tileData.Find(FVector(i, j, k));
			//	if (transform) {
			//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, transform->ToString());
			//	}
			//}
		}
	}

	
}

// Called every frame
void AHexagonalGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

