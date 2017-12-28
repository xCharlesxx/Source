// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomController.h"
#include "CPathFollowComponent.h"

 ACustomController::ACustomController(const FObjectInitializer& PCIP) : Super(PCIP.SetDefaultSubobjectClass<UCPathFollowComponent>(TEXT("PathFollowingComponent")))
 {
	
 }