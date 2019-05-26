// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "LengthTest.generated.h"

/**
 * 
 */
UCLASS()
class LABA_API ALengthTest : public AFunctionalTest
{
	GENERATED_BODY()

private:
	bool IsReady();

	UPROPERTY()
		class UVisualManager* VisManag;

	UPROPERTY()
		class UUIMemento* UIMem;

	UFUNCTION()
		void StartTest();

	UFUNCTION()
		void Tick(float DeltaSeconds);

	UFUNCTION()
		void PrepareTest();

	UFUNCTION()
		bool Length();

};
