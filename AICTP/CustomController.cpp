// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomController.h"
#include "CPathFollowComponent.h"
#include "Engine/World.h"
#include "Ball.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/AI/Navigation/RecastNavMesh.h"
//#include "NavigationSystem.generated.h"

 ACustomController::ACustomController(const FObjectInitializer& PCIP) : Super(PCIP.SetDefaultSubobjectClass<UCPathFollowComponent>(TEXT("PathFollowingComponent")))
 {
	 //auto world = GetWorld(); 
	 //auto navSystem = world->GetNavigationSystem(); 
	 //auto navData = navSystem->GetMainNavData(FNavigationSystem::DontCreate); 
	 //const ARecastNavMesh* navMesh = Cast<ARecastNavMesh>(navData); 
	 //auto loc = GetActorForwardVector();
		//      //GetControlledPawn();
	 //auto extent = FVector(100.0f, 100.0f, 100.0f);
	 //NavNodeRef poly = navMesh->FindNearestPoly(loc, extent, navData->GetDefaultQueryFilter());
	 //auto areaID = navMesh->GetPolyAreaID(poly);
	 //AddComponent(FName("Ball"), false, FTransform(FVector::OneVector), NULL);
	 //this->sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sphere"));
	 //this->sphere->AttachTo(GetRootComponent()); 
	 //static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")); 
	 //this->sphere->SetStaticMesh(SphereMeshAsset.Object); 
	 //= GetWorld()->SpawnActor<Ball>(FVector::OneVector, FRotator::ZeroRotator, spawnInfo);
	 //FSphere* phere = GetWorld()->SpawnActor<FSphere>(FSphere, FVector::OneVector, FRotator::ZeroRotator, spawnInfo);

	 
	/* CPathFollowComp = CreateDefaultSubobject<UCPathFollowComponent>(TEXT("CPathFollowComponent"));
	 CPathFollowComp->OnRequestFinished.AddUObject(this, &AAIController::OnMoveCompleted);*/
 }


 //const FNavAgentProperties& AgentProperties,
 FPathFindingResult ACustomController::FindPath(const FPathFindingQuery& Query) const
 {
	 // wrangle a 'this' of the correct type
	 const ANavigationData* NavData = Query.NavData.Get();
	 //const ACustomController* Custom = dynamic_cast<const ACustomController*>(NavData);
	 //check(Custom != nullptr);
	 //
	 //if (Custom == nullptr)
	 //{
		// return ENavigationQueryResult::Error;
	 //}

	 FPathFindingResult Result(ENavigationQueryResult::Error);

	 // create a new path if we need to, or reuse an existing one
	 Result.Path = Query.PathInstanceToFill.IsValid() ? Query.PathInstanceToFill : NavData->CreatePathInstance<FNavigationPath>(Query);

	 FNavigationPath* NavPath = Result.Path.Get();

	 if (NavPath != nullptr)
	 {
		 if ((Query.StartLocation - Query.EndLocation).IsNearlyZero())
		 {
			 Result.Path->GetPathPoints().Reset();
			 Result.Path->GetPathPoints().Add(FNavPathPoint(Query.EndLocation));
			 Result.Result = ENavigationQueryResult::Success;
		 }
		 else if (Query.QueryFilter.IsValid())
		 {
			 PathFindingAlgorithm(Query.StartLocation, Query.EndLocation, *NavPath);
			 
			 // run your pathfinding algorithm from Query.StartLocation to Query.EndLocation here,
			 // adding each point on the path to NavPath->GetPathPoints()
			 // the path must contain at least 2 points that aren't the start location
			 
			 // if your algorithm can only find a partial path call NavPath->SetIsPartial(true)
			 // and remember to check if Query.bAllowPartialPaths is set
			 // if it isn't, you should return ENavigationQueryResult::Fail

			 // and finally, remember to call this!
			 NavPath->MarkReady();
			 
			 Result.Result = ENavigationQueryResult::Success;
		 }
	 }

	 return Result;
 }



 bool ACustomController::PathFindingAlgorithm(FVector startLoc, FVector endLoc, FNavigationPath& path) const
 {
	 //Maybe store this in init 
	// m_nodePool = new (malloc(sizeof(CNodePool))) CNodePool(m_maxNodes);
	 if (!m_nodePool)
		 UE_LOG(LogTemp, Warning, TEXT("Error: Out of Memory"));

	 UE_LOG(LogTemp, Warning, TEXT("Entered PathFindingAlgorithm"));
	 auto world = GetWorld();
	 auto navSystem = world->GetNavigationSystem();
	 auto navData = navSystem->GetMainNavData(FNavigationSystem::DontCreate);
	 const ARecastNavMesh* navMesh = Cast<ARecastNavMesh>(navData);
	 FNavMeshNodeFlags flags = navMesh->GetFlags(); 
	 auto loc = startLoc;
	 /*GetControlledPawn();*/
	 auto extent = FVector(100.0f, 100.0f, 100.0f);
	 NavNodeRef startRef = navMesh->FindNearestPoly(loc, extent, navData->GetDefaultQueryFilter());
	 auto areaID = navMesh->GetPolyAreaID(startRef);
	 TArray<NavNodeRef> polyPool;
	 GetAllPolys(polyPool);
	 //ABall * balls[50];
	 for (int i = 0; i < polyPool.Num(); i++)
	 {
		 FVector center; 
		 navMesh->GetPolyCenter(polyPool[i], center);
		// spawnBall(center, FColor().Blue); 
		 m_nodePool->getNode(polyPool[i], true); 
		 m_nodePool->getNodeAtPoly(polyPool[i])->pos = center; 
		 //FActorSpawnParameters spawnInfo;
		 //spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		 //ABall* ball = GetWorld()->SpawnActor<ABall>(ABall::StaticClass(), FTransform(FVector(center.X, center.Y + 5, center.Z)), spawnInfo);
		 //Cannot edit component properties outside of constructor?!
		 //ball->Colour(FColor::Blue);
		 //balls[i] = ball; 
	 }
	 TArray<FNavPathPoint>& pathPoints = path.GetPathPoints(); 
	 pathPoints.Empty(); 
	 pathPoints.Add(startLoc);
	// navMesh->GetPolyFlags(areaID, flags);
	 //getNode = true FindNode = false; 

	 CNode* startNode = m_nodePool->getNode(startRef, true);  
	 startNode->pos = startLoc; 
	 startNode->parentId = 0; 
	 startNode->cost = 0;
	 startNode->total = Dist(&startLoc, &endLoc);
	 m_openList->push(startNode); 
	 CNode* lastBestNode = startNode; 
	 float lastBestNodeCost = startNode->total; 
	 const int loopLimit = m_nodePool->getMaxNodes() + 1; 
	 bool pathFound = false; 
	 int loopCounter = 0;
	 NavNodeRef finalPoly = navMesh->FindNearestPoly(endLoc, extent, navData->GetDefaultQueryFilter());
	 while (!m_openList->empty())
	 {
		 //break;

		 //Remove node from openlist and mark as closed 
		 CNode* bestNode = m_openList->pop();
		 //spawnBall(bestNode->pos, FColor().Blue);
		 bestNode->flags = NODE_CLOSED;

		 //Path has been found
		 if (bestNode->id == finalPoly)
		 {
			 UE_LOG(LogTemp, Warning, TEXT("Path Has Been Found!"));
			 //lastBestNode = bestNode;
			 TArray<FVector> path;
			 while (bestNode->parentId)
			 {
				 path.Add(bestNode->pos);
				 bestNode = bestNode->parentId;
			 }
			 //Reverse path
			 for (int i = path.Num()-1; i >= 0; --i)
			 {
				 pathPoints.Add(path[i]);
				 spawnBall(path[i], FColor().Blue);
			 }
			 //pathPoints.Add(bestNode->pos);
			 pathPoints.Add(endLoc);
			 break;
		 }

		 loopCounter++;

		 //Incase infinite loop
		 if (loopCounter >= loopLimit * 2)
		 {
			 UE_LOG(LogTemp, Warning, TEXT("Error: Loop Counter has exceeded normal limits"));
			 break;
		 }

		 const NavNodeRef bestRef = bestNode->id;

		 //NavNodeRef parentRef = 0; 
		 //Set parentref if bestref has a parent
		 //if (bestNode->parentId)
			// parentRef = m_nodePool->getNodeAtPoly(bestNode->parentId)->id; 

		 bool hasFoundNextLink = false;
		 //while (!hasFoundNextLink)
		// {
		 TArray<CNode> temp;
		 if (!GetPolyNeighbors(bestNode->id, temp))
			 UE_LOG(LogTemp, Warning, TEXT("Error: Couldn't get PolyNeighbours"));
		 TArray<CNode*> neighbours;
		 for (int i = 0; i < temp.Num(); i++)
			 neighbours.Add(m_nodePool->getNodeAtPoly(temp[i].id));
		 //Make sure Neighbours are valid 
		 for (int i = 0; i < neighbours.Num(); i++)
		 {
			 if (!neighbours[i]->id || neighbours[i] == bestNode->parentId)
				 neighbours.RemoveAt(i);
			 else if (neighbours[i]->parentId == 0)
				 neighbours[i]->parentId = bestNode;
		 }


		 /*CNode* neighbourNode = m_nodePool->getNode(neighbours[0], true);
		 if (!neighbourNode)
		 {
			 UE_LOG(LogTemp, Warning, TEXT("Out of nodes"));
			 continue;
		 }*/
		 //create ball at position to show nav path finding 
		 for (int i = 0; i < neighbours.Num(); i++)
		 {
			 CNode* nodeRef = m_nodePool->getNodeAtPoly(neighbours[i]->id);

			 if (nodeRef->flags == NODE_CLOSED)
				 break;
			 if (nodeRef->flags == NODE_OPEN)
			 {
				 //Check if node is easier to traverse from this direction
				 if (nodeRef->cost > Dist(&nodeRef->pos, &startLoc))
					 nodeRef->cost = Dist(&nodeRef->pos, &startLoc);
				 if (nodeRef->total > (nodeRef->cost + Dist(&nodeRef->pos, &endLoc)))
				 {
					 nodeRef->total = nodeRef->cost + Dist(&nodeRef->pos, &endLoc);
					 nodeRef->parentId = bestNode;
				 }

				 m_openList->modify(nodeRef);
			 }
			 //If node has never been visited before
			 else
			 {
				 nodeRef->cost = Dist(&nodeRef->pos, &startLoc);
				 nodeRef->total = nodeRef->cost + Dist(&nodeRef->pos, &endLoc);
				 m_openList->push(nodeRef);
				 nodeRef->flags = NODE_OPEN;
			 }
			 //spawnBall(nodeRef->pos, FColor().Blue);
		 }
		 // hasFoundNextLink = true; 
	//  }
		 //return true; 
	 }
	 return true; 
 }

 bool ACustomController::GetAllPolys(TArray<NavNodeRef>& Polys) const
 {
	 //Get Nav Data
	 const ANavigationData* NavData = CGetNavData();

	 const ARecastNavMesh* NavMesh = Cast<ARecastNavMesh>(NavData);
	 if (!NavMesh)
		 return false;
	 

	 TArray<FNavPoly> EachPolys;
	 for (int32 v = 0; v < NavMesh->GetNavMeshTilesCount(); v++)
	 {

		 //CHECK IS VALID FIRST OR WILL CRASH!!! 
		 // use continue in case the valid polys are not stored sequentially
		 if (!TileIsValid(NavMesh, v))
		 {
			 continue;
		 }
		 NavMesh->GetPolysInTile(v, EachPolys);
	 }

	 //Add polys
	 for (int32 v = 0; v < EachPolys.Num(); v++)
	 	 Polys.Add(EachPolys[v].Ref);
	 

	 return true;
 }
 TArray<AActor*> ACustomController::GetActorsWithName(FString staticMesh, FString skeletalMesh = "") const
 {
	 TArray<AActor*> result; 
	 for (TActorIterator<AStaticMeshActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	 {
		 // Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		 AStaticMeshActor *Mesh = *ActorItr;
		 if (ActorItr->GetName().Contains(staticMesh))
			 result.Add(*ActorItr); 
	 }
	 if (skeletalMesh != "")
	 for (TActorIterator<ACharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	 {
		 // Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		 ACharacter *Mesh = *ActorItr;
		 if (ActorItr->GetName().Contains(skeletalMesh))
			 result.Add(*ActorItr);
	 }
	 return result; 
 }
 bool ACustomController::GetPolyNeighbors(NavNodeRef PolyID, TArray<CNode>& Neighbors) const
 {
	 float searchDistance = 1250; 
	 TArray<NavNodeRef> polyPool;
	 GetAllPolys(polyPool);
	 auto hitOut = FHitResult(ForceInit);
	 //Ignore floors when checking for interruptions
	 TArray<AActor*> temp = GetActorsWithName("Floor", "Character");
	 TArray<AActor*>& ActorsToIgnore = temp; 
	 FCollisionQueryParams TraceParams(FName(TEXT("VictoryCore Trace")), true, ActorsToIgnore[0]);
	 TraceParams.bTraceComplex = true;
	 //Ignore Actors
	 TraceParams.AddIgnoredActors(ActorsToIgnore);
	 //Check distance between poly and all other polys and return closest
	 for (int i = 0; i < polyPool.Num(); i++)
		 //If within distance
		 if ((Dist(&m_nodePool->getNodeAtPoly(polyPool[i])->pos, &m_nodePool->getNodeAtPoly(PolyID)->pos) < searchDistance))
		 { //and nothing between points
			 GetWorld()->LineTraceSingleByChannel(hitOut, m_nodePool->getNodeAtPoly(polyPool[i])->pos, m_nodePool->getNodeAtPoly(PolyID)->pos, ECC_Pawn, TraceParams);
				 if (hitOut.GetActor() == NULL)
					 //and not node making query
					 if (polyPool[i] != PolyID)
						 Neighbors.Add(*m_nodePool->getNodeAtPoly(polyPool[i]));
		 }
		
	 if (Neighbors.Num() == 0)
		 return false; 
	/*const NavNodeRef PolyRef = static_cast<NavNodeRef>(PolyID);
	FVector *center = &m_nodePool->getNodeAtPoly(PolyRef)->pos;
	FVector *extents = new FVector(100.0f, 100.0f, 100.0f);*/
//	FVector *bmin, *bmax;
	
	//Sub(bmin, center, extents);
	//Add(bmax, center, extents);

	// Find tiles the query touches.
	//int minx, miny, maxx, maxy;
	//m_nav->calcTileLoc(bmin, &minx, &miny);
	//m_nav->calcTileLoc(bmax, &maxx, &maxy);
	//
	//ReadTilesHelper TileArray;

	//int n = 0;
	//for (int y = miny; y <= maxy; ++y)
	//{
	//	for (int x = minx; x <= maxx; ++x)
	//	{
	//		int nneis = m_nav->getTileCountAt(x, y);
	//		const dtMeshTile** neis = (const dtMeshTile**)TileArray.PrepareArray(nneis);

	//		m_nav->getTilesAt(x, y, neis, nneis);
	//		for (int j = 0; j < nneis; ++j)
	//		{
	//			n += queryPolygonsInTile(neis[j], bmin, bmax, filter, polys + n, maxPolys - n);
	//			if (n >= maxPolys)
	//			{
	//				*polyCount = n;
	//				return DT_SUCCESS | DT_BUFFER_TOO_SMALL;
	//			}
	//		}
	//	}
	//}
	//*polyCount = n;

	return true;
 }


 void ACustomController::spawnBall(FVector loc, FColor colour) const
 {
	// FActorSpawnParameters spawnInfo;
	// spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	 UE_LOG(LogTemp, Warning, TEXT("Spawned Sphere"));
	 ABall* ball = GetWorld()->SpawnActorDeferred<ABall>(ABall::StaticClass(), FTransform(FVector(loc.X, loc.Y + 5, loc.Z)));
	 ball->Colour(colour); 
	 ball->FinishSpawning(FTransform(FVector(loc.X, loc.Y + 5, loc.Z)));
 }


 void ACustomController::FindPathForMoveRequest(const FAIMoveRequest & MoveRequest, FPathFindingQuery & Query, FNavPathSharedPtr & OutPath) const
 {
	 FPathFindingResult r = this->FindPath(Query);
	 SCOPE_CYCLE_COUNTER(STAT_AI_Overall);

	 UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
	 if (NavSys)
	 {
		 FPathFindingResult PathResult = NavSys->FindPathSync(Query);
		 if (PathResult.Result != ENavigationQueryResult::Error)
		 {
			 if (PathResult.IsSuccessful() && PathResult.Path.IsValid())
			 {
				 if (MoveRequest.IsMoveToActorRequest())
				 {
					 PathResult.Path->SetGoalActorObservation(*MoveRequest.GetGoalActor(), 100.0f);
				 }

				 PathResult.Path->EnableRecalculationOnInvalidation(true);
				 OutPath = PathResult.Path;
			 }
		 }
		 else
		 {
			/* UE_VLOG(this, LogAINavigation, Error, TEXT("Trying to find path to %s resulted in Error")
				 , MoveRequest.IsMoveToActorRequest() ? *GetNameSafe(MoveRequest.GetGoalActor()) : *MoveRequest.GetGoalLocation().ToString());
			 UE_VLOG_SEGMENT(this, LogAINavigation, Error, GetPawn() ? GetPawn()->GetActorLocation() : FAISystem::InvalidLocation
				 , MoveRequest.GetGoalLocation(), FColor::Red, TEXT("Failed move to %s"), *GetNameSafe(MoveRequest.GetGoalActor()));*/
		 }
	 }
 }
