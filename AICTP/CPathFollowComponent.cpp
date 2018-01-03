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
	 UE_LOG(LogTemp, Warning, TEXT("SetMovementComponent"));
	 Super::SetMovementComponent(MoveComp);

	 CharacterMoveComp = Cast<UCharacterMovementComponent>(MovementComp);
 }
 
 void UCPathFollowComponent::SetMoveSegment(int32 SegmentStartIndex)
 {
	UE_LOG(LogTemp, Warning, TEXT("SetMoveSegment"));
	Super::SetMoveSegment(SegmentStartIndex);
	
	if (CharacterMoveComp != NULL)
	{
		const FNavPathPoint& SegmentStart = Path->GetPathPoints()[MoveSegmentStartIndex];

		if (FNavAreaHelper::HasJumpFlag(SegmentStart))
		{
			// jump! well... fly-in-straight-line!
			UE_LOG(LogTemp, Warning, TEXT("JUMPING"));
			//CharacterMoveComp->SetMovementMode(MOVE_);
			//CharacterMoveComp->JumpZVelocity = 800;
			CharacterMoveComp->DoJump(true); 
			//CharacterMoveComp->Launch(CharacterMoveComp->GetCurrentAcceleration());
		}
		else
		{
			// regular move
			UE_LOG(LogTemp, Warning, TEXT("Walking"));
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

// Called every frame
//void UCCPathFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

