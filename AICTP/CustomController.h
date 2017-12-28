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
};
