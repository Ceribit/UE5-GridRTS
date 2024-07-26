// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawner.h"
#include "UnitData.h"

// Sets default values
AUnitSpawner::AUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableObject(TEXT("DataTable'/Game/Core/Unit/DT_UnitData.DT_UnitData'"));
	DataTable = DataTableObject.Object;
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



	ADefaultCharacter* NewCharacter = Cast<ADefaultCharacter>(GetWorld()->SpawnActor(UnitClass, &Location, &Rotation));

	NewCharacter->SetActorLocationAndRotation(Location, Rotation);


	if (NewCharacter) {

		if (DataTable)
		{
			FUnitData* RowData = DataTable->FindRow<FUnitData>(FName(TeamName), "");
			if (RowData)
			{
				NewCharacter->SetUnitData(*RowData);
			}
		}

		NewCharacter->UpdateHealthBar();
		NewCharacter->SpawnDefaultController();
		Location = Grid->GetTilePositionFromOffset(SpawnLocation);
		NewCharacter->UnitMoveCommand(Location);
	}
}

void AUnitSpawner::SetTeam(FString NewTeamName) {
	this->TeamName = NewTeamName;
}