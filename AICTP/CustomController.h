// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "CustomController.generated.h"

UCLASS()
class ACustomController : public AAIController
{
	GENERATED_BODY()
public:
	ACustomController(const FObjectInitializer& PCIP); 
	//virtual void FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query, FNavPathSharedPtr& OutPath) const override;
	virtual FAIRequestID RequestPathAndMove(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query) override;
	FPathFindingResult FindPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query);
	bool PathFindingAlgorithm(FVector startLoc, FVector endLoc, FNavigationPath& result);
};
struct QueryData
{
	struct dtNode* lastBestNode;
	float lastBestNodeCost;
	FVector startRef, endRef;
	float startPos[3], endPos[3];
};

QueryData m_query;				///< Sliced query state.

class NodePool* m_nodePool;		///< Pointer to node pool.
class NodeQueue* m_openList;		///< Pointer to open list queue.

int m_queryNodes;