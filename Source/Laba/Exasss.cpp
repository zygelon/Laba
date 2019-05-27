// Fill out your copyright notice in the Description page of Project Settings.


/**

  Exasss.cpp

  Purpose: tests sorting

 */

#include "Exasss.h"
#include "UVisualManager.h"

bool AExasss::IsReady()
{
//	Super::IsReady();
	return IsValid(UVisualManager::GetVisualManager());

}

void AExasss::StartTest()
{
	Super::StartTest();
	//PrimaryActorTick.bCanEverTick = true;
	
	
}

void AExasss::Tick(float DeltaSeconds)
{
	if (!VisManag) FinishTest(EFunctionalTestResult::Error, "VisManag NULLPTR");
	if (VisManag->bIsSorted)
	{
		if (IsSorted()) FinishTest(EFunctionalTestResult::Succeeded, "Sorted");
		else FinishTest(EFunctionalTestResult::Failed, "Not Sorted");
	}
}

void AExasss::PrepareTest()
{
	Super::PrepareTest();
	VisManag = UVisualManager::GetVisualManager();
}

bool AExasss::IsSorted()
{
	//UGameplayStatics::GetPlayerController(GetWorld(), 0);
	for (int i = 0; i < VisManag->Cells.Num() - 1; ++i)
		if (VisManag->Cells[i]->GetNum() > VisManag->Cells[i + 1]->GetNum())
			return false;
	return true;
}
