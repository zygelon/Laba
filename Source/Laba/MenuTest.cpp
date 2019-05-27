// Fill out your copyright notice in the Description page of Project Settings.

/**

  MenuTest.cpp

  Purpose: tests spawn func

 */

#include "MenuTest.h"
#include "UVisualManager.h"

bool AMenuTest::IsReady()
{
	//	Super::IsReady();
	return IsValid(UVisualManager::GetVisualManager());

}

void AMenuTest::StartTest()
{
	Super::StartTest();
	//PrimaryActorTick.bCanEverTick = true;


}

void AMenuTest::Tick(float DeltaSeconds)
{
	if (!VisManag) FinishTest(EFunctionalTestResult::Error, "VisManag NULLPTR");
	if (VisManag->Cell_BP)
	{
		if ((IsSpawned())) FinishTest(EFunctionalTestResult::Succeeded, "Spawned");
		else FinishTest(EFunctionalTestResult::Failed, "Not Spawned");
	}
}

void AMenuTest::PrepareTest()
{
	Super::PrepareTest();
	VisManag = UVisualManager::GetVisualManager();
}

bool AMenuTest::IsSpawned()
{
	if (VisManag->Cells.Num() == 0)
		return false;
	else
		return true;
}
