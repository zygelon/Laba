// Fill out your copyright notice in the Description page of Project Settings.

/**

  LengthTest.h

  Purpose: tests length func

 */

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
		* checks if setted length = created length
		*
		* @brief Length
		*/
		bool Length();

};
