// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"
#include "CPathFollowComponent.generated.h"

class UNavMovementComponent; 
class UCharacterMovementComponent; 

UCLASS()
class AICTP_API UCPathFollowComponent : public UPathFollowingComponent
{
	GENERATED_BODY()
	UCPathFollowComponent(const FObjectInitializer& PCIP);
protected:
	UPROPERTY(transient)
	class UCharacterMovementComponent * CharacterMoveComp;

public:	
	
	// used to detect properties of a path's segment a character is about to follow
	virtual void SetMoveSegment(int32 SegmentStartIndex) override;
	// used to cache UCharacterMovementComponent we're using in SetMoveSegment implementation
	virtual void SetMovementComponent(UNavMovementComponent* MoveComp) override;
	
};
