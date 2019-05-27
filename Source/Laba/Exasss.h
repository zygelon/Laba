// Fill out your copyright notice in the Description page of Project Settings.

/**

  Exasss.h

  Purpose: tests sorting

 */

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "Exasss.generated.h"

/**
 * 
 */
UCLASS()
class LABA_API AExasss : public AFunctionalTest
{
	GENERATED_BODY()
private:
	bool IsReady();

	UPROPERTY()
	class UVisualManager* VisManag;

	UFUNCTION()
	/*
	* starts test
	*
	* @brief StartTest
	*/
	void StartTest();

	UFUNCTION()
	void Tick(float DeltaSeconds);

	UFUNCTION()
	/*
	* prepares test
	*
	* @brief PrepareTest
	*/
	void PrepareTest();

	UFUNCTION()
	/*
	* checks if sorted
	*
	* @brief IsSorted
	*/
	bool IsSorted();
};
