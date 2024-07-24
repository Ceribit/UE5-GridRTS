// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavMesh/RecastNavMesh.h"
#include "HexagonalGrid.h"
#include "GraphAStarNavMesh.generated.h"

/*
 *  TQueryFilter (FindPath's parameter) filter class decides which graph edges can be used and at what cost.
 */
struct FGridPathFilter {
	FGridPathFilter(const AGraphAStarNavMesh &InNavMeshRef) : NavMeshRef(InNavMeshRef) {}
	
	float GetHeuristicScale() const;

	float GetHeuristicCost(const int32 StartNodeRef, const int32 EndNodeRef) const;

	float GetTraversalCost(const int32 StartNodeRef, const int32 EndNodeRef) const;

	bool IsTraversalAllowed(const int32 NodeA, const int32 NodeB) const;

	//bool WantsPartialSolution();

protected:
	// A reference to the base NavMesh
	const AGraphAStarNavMesh& NavMeshRef;
};

struct FHexNavMeshPath : public FNavMeshPath
{
	FORCEINLINE
	virtual double GetCostFromIndex(int32 PathPointIndex) const override
	{
		return CurrentPathCost;
	}

	FORCEINLINE
	virtual double GetLengthFromPosition(FVector SegmentStart, uint32 NextPathPointIndex) const override
	{
		return PathPoints.Num() - 1;

	}

	float CurrentPathCost{ 0 };
};
/**
 * 
 */
UCLASS()
class GRIDBASEDRTS_API AGraphAStarNavMesh : public ARecastNavMesh
{
	GENERATED_BODY()

public:
	static FPathFindingResult FindPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query);

	UFUNCTION(BlueprintCallable)
	void SetHexGrid(class AHexagonalGrid* HexGrid);

	/* Type used as identification of nodes in the graph */
	typedef int32 FNodeRef;

	/* Returns number of neighbors that the graph node identified with NodeRef has */
	int32 GetNeighbourCount(FNodeRef NodeRef) const;

	/* Returns whether given node identification is correct */
	bool IsValidRef(FNodeRef NodeRef) const;

	/* Returns neighbor ref */
	//FNodeRef GetNeighbour(const FNodeRef NodeRef, const int32 NeiIndex) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GraphAStarExample|NavMesh")
		class AHexagonalGrid* HexGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GraphAStarExample|NavMesh")
		float PathPointZOffset{ 0.f };
};
