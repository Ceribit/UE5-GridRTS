// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawner.h"

// Sets default values
AUnitSpawner::AUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AUnitSpawner::SetGrid(AHexagonalGrid* NewGrid) {
	this->Grid = NewGrid;
}

void AUnitSpawner::SetUnitSpawnLocation(FIntPoint Index){
	this->SpawnLocation = Index;
}

void AUnitSpawner::CreateUnit() {
	FVector Location(0.f, 0.f, 0.f);
	FRotator Rotation(0.f, 0.f, 0.f);
	ADefaultCharacter* NewCharacter = Cast<ADefaultCharacter>(GetWorld()->SpawnActor(UnitClass,&Location, &Rotation));
	if (NewCharacter) {
		NewCharacter->SpawnDefaultController();
		Location = Grid->GetTilePositionFromOffset(SpawnLocation);
		NewCharacter->UnitMoveCommand(Location);
	}
}
