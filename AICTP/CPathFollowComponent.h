// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"
#include "CPathFollowComponent.generated.h"

class UNavMovementComponent; 
class UCharacterMovementComponent; 

UCLASS()
class UCPathFollowComponent : public UPathFollowingComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(transient)
	UCharacterMovementComponent * CharacterMoveComp;

public:	
	UCPathFollowComponent(const FObjectInitializer& PCIP);
	// used to detect properties of a path's segment a character is about to follow
	virtual void SetMoveSegment(int32 SegmentStartIndex) override;
	// used to cache UCharacterMovementComponent we're using in SetMoveSegment implementation
	virtual void SetMovementComponent(UNavMovementComponent* MoveComp) override;
};
