// Fill out your copyright notice in the Description page of Project Settings.


#include "LengthTest.h"
#include "UVisualManager.h"
#include "UIMemento.h"

bool ALengthTest::IsReady()
{
	//	Super::IsReady();
	return IsValid(UVisualManager::GetVisualManager());
}

void ALengthTest::StartTest()
{
	Super::StartTest();
	//PrimaryActorTick.bCanEverTick = true;


}

void ALengthTest::Tick(float DeltaSeconds)
{
	if (!VisManag) FinishTest(EFunctionalTestResult::Error, "VisManag NULLPTR");
	if (VisManag->Length)
	{
		if ((Length())) FinishTest(EFunctionalTestResult::Succeeded, "Destroyed");
		else FinishTest(EFunctionalTestResult::Failed, "Not Destroyed");
	}
}

void ALengthTest::PrepareTest()
{
	Super::PrepareTest();
	VisManag = UVisualManager::GetVisualManager();
}

bool ALengthTest::Length()
{
	if (VisManag->Length = UIMem->SetLength())
		return true;
	else
		return false;
}
