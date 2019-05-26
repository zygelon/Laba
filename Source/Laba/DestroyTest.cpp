// Fill out your copyright notice in the Description page of Project Settings.


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
	if (VisManag->Cell_BP)
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