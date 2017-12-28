// Fill out your copyright notice in the Description page of Project Settings.

#include "CUNavAreaJump.h"


 UCUNavAreaJump::UCUNavAreaJump(const class FObjectInitializer& PCIP)
	 : Super(PCIP)
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	FNavAreaHelper::Set(AreaFlags, ENavAreaFlag::Jump);
}