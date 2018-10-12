// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IGC.generated.h"

/**
 * 
 */
UCLASS()
class IGCEDITOREXTENSIONS_API UIGC : public UObject
{
	GENERATED_BODY()

	UIGC();
	
public:
	UPROPERTY(EditAnywhere, Category = "Session")
	FString SpeakerName;

	UPROPERTY(VisibleAnywhere, Category = "Session")
	FDateTime SessionStart;

	UPROPERTY(VisibleAnywhere, Category = "Session")
	int SessionDuration;

};
