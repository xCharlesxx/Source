// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomController.h"
#include "CPathFollowComponent.h"
//#include "Engine\World.h"
//#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
//#include "Runtime/Engine/Classes/AI/Navigation/RecastNavMesh.h"
//#include "NavigationSystem.generated.h"

 ACustomController::ACustomController(const FObjectInitializer& PCIP) : Super(PCIP.SetDefaultSubobjectClass<UCPathFollowComponent>(TEXT("PathFollowingComponent")))
 {
	 //auto world = GetWorld(); 
	 //auto navSystem = world->GetNavigationSystem(); 
	 //auto navData = navSystem->GetMainNavData(FNavigationSystem::DontCreate); 
	 //const ARecastNavMesh* navMesh = Cast<ARecastNavMesh>(navData); 
	 //auto loc = GetControlledPawn();
	 //auto extent = FVector(100.0f, 100.0f, 100.0f);
	 //NavNodeRef poly = navMesh->FindNearestPoly(loc, extent, navData->GetDefaultQueryFilter());

	 //auto areaID = navMesh->GetPolyAreaID(poly);

 }

 FPathFindingResult ACustomController::FindPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query)
 {
	 // wrangle a 'this' of the correct type
	 const ANavigationData* NavData = Query.NavData.Get();
	 const ACustomController* Custom = dynamic_cast<const ACustomController*>(NavData);
	 check(Custom != nullptr);
	 
	 if (Custom == nullptr)
	 {
		 return ENavigationQueryResult::Error;
	 }

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
 bool ACustomController::PathFindingAlgorithm(FVector startLoc, FVector endLoc, FNavigationPath& path)
 {
	 TArray<FNavPathPoint>& pathPoints = path.GetPathPoints(); 
	 pathPoints.Add(startLoc);
	// m_nodePool->clear(); 
	 if (startLoc == endLoc)
		 return true;
	 
	 
 }
 //void ACustomController::FindPathForMoveRequest(const FAIMoveRequest & MoveRequest, FPathFindingQuery & Query, FNavPathSharedPtr & OutPath) const
 //{
	// SCOPE_CYCLE_COUNTER(STAT_AI_Overall);

	// UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
	// if (NavSys)
	// {
	//	 FPathFindingResult PathResult = NavSys->FindPathSync(Query);
	//	 if (PathResult.Result != ENavigationQueryResult::Error)
	//	 {
	//		 if (PathResult.IsSuccessful() && PathResult.Path.IsValid())
	//		 {
	//			 if (MoveRequest.IsMoveToActorRequest())
	//			 {
	//				 PathResult.Path->SetGoalActorObservation(*MoveRequest.GetGoalActor(), 100.0f);
	//			 }

	//			 PathResult.Path->EnableRecalculationOnInvalidation(true);
	//			 OutPath = PathResult.Path;
	//		 }
	//	 }
	//	 else
	//	 {
	//		 UE_LOG(LogTemp, Warning, TEXT("Couldn't find path for move request"));
	//	 }
	// }
 //}

 FAIRequestID ACustomController::RequestPathAndMove(const FAIMoveRequest & MoveRequest, FPathFindingQuery & Query)
 {
	 FAIRequestID MoveId = FAIRequestID::InvalidRequest;

	 FNavPathSharedPtr FoundPath;
	 FindPathForMoveRequest(MoveRequest, Query, FoundPath);

	 if (FoundPath.IsValid())
	 {
		 MoveId = RequestMove(MoveRequest, FoundPath);
	 }

	 return MoveId;
 }
