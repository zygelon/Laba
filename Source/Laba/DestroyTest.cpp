// Fill out your copyright notice in the Description page of Project Settings.

/**

  DestroyTest.cpp

  Purpose: tests destroy func

 */


#include "DestroyTest.h"
#include "UVisualManager.h"

bool ADestroyTest::IsReady()
{
	//	Super::IsReady();
	return IsValid(UVisualManager::GetVisualManager());

}

void ADestroyTest::StartTest()
{
	Super::StartTest();
	//PrimaryActorTick.bCanEverTick = true;


}

void ADestroyTest::Tick(float DeltaSeconds)
{
	if (!VisManag) FinishTest(EFunctionalTestResult::Error, "VisManag NULLPTR");
	if (VisManag->bIsSorted)
	{
		if ((IsDestroyed())) FinishTest(EFunctionalTestResult::Succeeded, "Destroyed");
		else FinishTest(EFunctionalTestResult::Failed, "Not Destroyed");
	}
}

void ADestroyTest::PrepareTest()
{
	Super::PrepareTest();
	VisManag = UVisualManager::GetVisualManager();
}

bool ADestroyTest::IsDestroyed()
{
	if (VisManag->Cells.Num() == 0)
		return true;
	else
		return false;
}