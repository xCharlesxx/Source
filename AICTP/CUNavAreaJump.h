// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Navigation/NavAreas/NavArea.h"
#include "AI/Navigation/RecastNavMesh.h"
#include "CUNavAreaJump.generated.h"


UENUM()
namespace ENavAreaFlag
{
	// up to 15 values
	enum Type
	{
		Default,
		Jump,
		Crouch,
		// and what not
	};
}

namespace FNavAreaHelper
{
	FORCEINLINE bool IsSet(uint16 Flags, ENavAreaFlag::Type Bit) { return (Flags & (1 << Bit)) != 0; }
	FORCEINLINE void Set(uint16& Flags, ENavAreaFlag::Type Bit) { Flags |= (1 << Bit); }

	FORCEINLINE bool IsNavLink(const FNavPathPoint& PathVert) { return (FNavMeshNodeFlags(PathVert.Flags).PathFlags & RECAST_STRAIGHTPATH_OFFMESH_CONNECTION) != 0; }
	FORCEINLINE bool HasJumpFlag(const FNavPathPoint& PathVert) { return (PathVert.Flags == ENavAreaFlag::Jump); }
		//IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::Jump); }
	FORCEINLINE bool HasCrouchFlag(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::Crouch); }
}

UCLASS()
class UCUNavAreaJump : public UNavArea
{
	GENERATED_BODY()

public:
	UCUNavAreaJump(const class FObjectInitializer& PCIP);
};


