// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GraphAStarNavMesh.h"
#include "HexagonalGrid.h"
#include "AIModule/Public/GraphAStar.h"


//==== FGridPathFilter functions implementation ===
// In these functions we do not check if the HexGrid is valid because it must be!
// Remember, if the HexGrid is a nullptr we will never use this code
// but we fallback to the RecastNavMesh implementation of it.

float FGridPathFilter::GetHeuristicScale() const
{
	// For the sake of simplicity we just return 1.f
	return 1.0f;
}

float FGridPathFilter::GetHeuristicCost(const int32 StartNodeRef, const int32 EndNodeRef) const
{
	return GetTraversalCost(StartNodeRef, EndNodeRef);
}

float FGridPathFilter::GetTraversalCost(const int32 StartNodeRef, const int32 EndNodeRef) const
{

		return 1.f;
}

bool FGridPathFilter::IsTraversalAllowed(const int32 NodeA, const int32 NodeB) const
{
	// If NodeB is a valid index of the GridTiles array we return bIsBlocking, 
	// if not we assume we can traverse so we return true.
	// Here you can make a more complex operation like use a line trace to see
	// there is some obstacles (like an enemy), in our example we just use a simple implementation

		return true;

}

//bool FGridPathFilter::WantsPartialSolution() const
//{
//	// Just return true
//	return true;
//}
//==== END OF FGridPathFilter functions implementation ====


FPathFindingResult AGraphAStarNavMesh::FindPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query)
{
	// =================================================================================================
	// The first part is the same of RecastNavMesh::FindPath implementation, the only difference is
	// the cast of ANavigationData to our class.


	// Because we are in a static function we don't have a "this" pointer and we can't access to class member variables like HexGrid
	// but luckily the FPathFindingQuery contain a pointer to the ANavigationData object.
	const ANavigationData* Self = Query.NavData.Get();
	check(Cast<const AGraphAStarNavMesh>(Self));

	// Now we can cast to our class, this will allow us to access the member variables (and functions).
	// NOTE: remember, our AGraphAStarNavMesh inherit from ARecastNavMesh that inherit from ANavigationData so we can do the cast.
	const AGraphAStarNavMesh* GraphAStarNavMesh{ Cast<const AGraphAStarNavMesh>(Self) };

	if (Self == NULL)
	{
		return ENavigationQueryResult::Error;
	}

	// This struct contains the result of our search and the Path that the AI will follow
	FPathFindingResult Result(ENavigationQueryResult::Error);

	return Result;
}


void AGraphAStarNavMesh::SetHexGrid(AHexagonalGrid* HGrid)
{
	if (HGrid)
	{
		// If the pointer is valid we will use our implementation of the FindPath function
		HexGrid = HGrid;
		FindPathImplementation = FindPath;
	}
	else
	{
		// If the pointer is not valid we will fallback to the default RecastNavMesh implementation
		// of the FindPath function (the standard navigation behavior)
		// You can also use FindPathImplementation = ARecastNavMesh::FindPath;
		// but i start from the assumption that we are inheriting from ARecastNavMesh
		HexGrid = nullptr;
		FindPathImplementation = Super::FindPath;
	}
}


//////////////////////////////////////////////////////////////////////////
// FGraphAStar: TGraph
// Functions implementation for our FGraphAStar struct
int32 AGraphAStarNavMesh::GetNeighbourCount(FNodeRef NodeRef) const
{
	return 6;
}

bool AGraphAStarNavMesh::IsValidRef(FNodeRef NodeRef) const
{
	//return HexGrid->GridCoordinates.IsValidIndex(NodeRef);
	return true;
}

//AGraphAStarNavMesh::FNodeRef
//AGraphAStarNavMesh::GetNeighbour(const FNodeRef NodeRef, const int32 NeiIndex) const
//{
//	//FHCubeCoord Neigh{ HexGrid->GetNeighbor(HexGrid->GridCoordinates[NodeRef], HexGrid->GetDirection(NeiIndex)) };
//	//return HexGrid->GridCoordinates.IndexOfByKey(Neigh);
//}
//////////////////////////////////////////////////////////////////////////