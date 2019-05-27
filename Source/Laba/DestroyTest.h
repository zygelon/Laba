// Fill out your copyright notice in the Description page of Project Settings.

/**

  DestroyTest.h

  Purpose: tests destroy func

 */

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "DestroyTest.generated.h"

/**
 *
 */
UCLASS()
class LABA_API ADestroyTest : public AFunctionalTest
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
		* checks if destroyed
		*
		* @brief IsDestroyed
		*/
		bool IsDestroyed();

};
