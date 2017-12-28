// Fill out your copyright notice in the Description page of Project Settings.

#include "CPathFollowComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "CUNavAreaJump.h"
#include "GameFramework/CharacterMovementComponent.h"

 UCPathFollowComponent::UCPathFollowComponent(const FObjectInitializer& PCIP) : Super(PCIP)
 {
	
 }

 void UCPathFollowComponent::SetMovementComponent(UNavMovementComponent* MoveComp)
 {
	 Super::SetMovementComponent(MoveComp);

	 CharacterMoveComp = Cast<UCharacterMovementComponent>(MovementComp);
 }

 void UCPathFollowComponent::SetMoveSegment(int32 SegmentStartIndex)
 {
	Super::SetMoveSegment(SegmentStartIndex);
	
	if (CharacterMoveComp != NULL)
	{
		const FNavPathPoint& SegmentStart = Path->GetPathPoints()[MoveSegmentStartIndex];

		if (FNavAreaHelper::HasJumpFlag(SegmentStart))
		{
			// jump! well... fly-in-straight-line!
			CharacterMoveComp->SetMovementMode(MOVE_Flying);
			CharacterMoveComp->DoJump(true); 
		}
		else
		{
			// regular move
			CharacterMoveComp->SetMovementMode(MOVE_Walking);
		}
	
	}
 }



// Sets default values for this component's properties
//AUCCPathFollowComponent::AUCCPathFollowComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<CCPathFollowComponent>(TEXT("PathFollowComponent")));
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void AUCCPathFollowComponent::BeginPlay()
//{
//	//Super::BeginPlay();
//
//	// ...
//	
//}
//
////Rama's UE4 Nav code to get all the nav polys!
//bool AUCCPathFollowComponent::NavPoly_GetAllPolys(TArray<NavNodeRef>& Polys)
//{
//	if (!MovementComp) return false;
//	//~~~~~~~~~~~~~~~~~~
//
//	//Get Nav Data
//	const ANavigationData* NavData = CCGetNavData();
//
//	const ARecastNavMesh* NavMesh = Cast<ARecastNavMesh>(NavData);
//	if (!NavMesh)
//	{
//		return false;
//	}
//
//	TArray<FNavPoly> EachPolys;
//	for (int32 v = 0; v < NavMesh->GetNavMeshTilesCount(); v++)
//	{
//
//		//CHECK IS VALID FIRST OR WILL CRASH!!! 
//		//     256 entries but only few are valid!
//		// use continue in case the valid polys are not stored sequentially
//		if (!TileIsValid(NavMesh, v))
//		{
//			continue;
//		}
//
//		NavMesh->GetPolysInTile(v, EachPolys);
//	}
//
//
//	//Add them all!
//	for (int32 v = 0; v < EachPolys.Num(); v++)
//	{
//		Polys.Add(EachPolys[v].Ref);
//	}
//}

// Called every frame
//void UCCPathFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

