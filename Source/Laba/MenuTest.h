// Fill out your copyright notice in the Description page of Project Settings.

/**

  MenuTest.h

  Purpose: tests spawn func

 */

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "MenuTest.generated.h"

/**
 * 
 */
UCLASS()
class LABA_API AMenuTest : public AFunctionalTest
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
		* checks if spawned
		*
		* @brief IsSpawned
		*/
		bool IsSpawned();

};
