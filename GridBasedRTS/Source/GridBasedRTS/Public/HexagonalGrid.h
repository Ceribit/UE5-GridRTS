// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Engine/Classes/Components/InstancedStaticMeshComponent.h" 
#include "Kismet/KismetMathLibrary.h"
#include "HexagonalGrid.generated.h"

UCLASS()
class GRIDBASEDRTS_API AHexagonalGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexagonalGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int height;
	int width;
	TMap<FVector2D,FTransform> tileData;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	//UStaticMeshComponent* StaticMesh;
};
