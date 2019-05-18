// Fill out your copyright notice in the Description page of Project Settings.

#include "VisualManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GenericPlatformProcess.h"
#include "Async.h"

// Sets default values
AVisualManager::AVisualManager() : bIsSorted(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//"Class'/Game/dice/D4_Dice_BP.D4_Dice_BP_C'"
	static ConstructorHelpers::FObjectFinder<UClass> Cell_BP_temp(
		TEXT("Class'/Game/Cell/BP_Cell.BP_Cell_C'"));
	if(Cell_BP_temp.Object)
		Cell_BP = Cell_BP_temp.Object;
}



void AVisualManager::SpawnCells()
{
	//atic ConstructorHelpers::FObjectFinder<UBlueprint> BP_Cell
	//(TEXT("Blueprint'/Game/Cell/BP_Cell.BP_Cell'"));
	//int t = 0;
	FVector SpawnPosition(390.000000, -240.000000,  130.000000);//spawn position
	for (int i = 0; i < Height;++i, SpawnPosition+=FVector(0,-25.f*Length,-25.f))//50 -size of cell edge
	{
		for (int j = 0; j < Length; ++j, SpawnPosition+=FVector(0,25.f,0))
		{
			//++t;
			//FRotator Rotation(0, 0, 0);

			//auto SpawnClass = 
			ACell* SpawnedCell = GetWorld()->SpawnActor<ACell>(Cell_BP, SpawnPosition, FRotator::ZeroRotator);
			SpawnedCell->InitNum(FMath::RandRange(0,360));
			//SpawnedCell->InitNum(t);
			Cells.Add(SpawnedCell);
		}
	}
}

void AVisualManager::DestroyCells()
{
	//if (true) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		//FString::Printf(TEXT("Memory Error" )));  }

	for (int i = 0; i < Cells.Num(); ++i)
		Cells[i]->Destroy();

	Cells.Empty();
}

void AVisualManager::BeginPlay()
{
	
}


void AVisualManager::StartVisualization()
{
	
	switch (CurrentSort)
	{
	case ESortType::Bubble:
		//Async<int>(EAsyncExecution::ThreadPool, [this]() {BubbleSort(); return 1; });
		Async<void>(EAsyncExecution::Thread, [this]() {
			BubbleSort();
		});
		break;
	case ESortType::Insertion:
		break;
	}
}

void AVisualManager::BubbleSort()
{
	for (int32 i=0; i < Cells.Num() - 1; i++)
	{
		for (int32 j=0; j < Cells.Num() - i - 1; j++)
			if (Cells[j]->GetNum() > Cells[j + 1]->GetNum())
			{
				//GetWorldTimerManager().SetTimer(VTimer, .f, false, 20.f,);
				VSwap(j, j + 1);
			}
	}
	//bIsSorted = true;
}

void AVisualManager::VSwap(int32 FirstIndex,  int32 SecondIndex)
{
	

	AsyncTask(ENamedThreads::GameThread, [&]() {
		FVector temp_loc = Cells[FirstIndex]->GetActorLocation();

		Cells[FirstIndex]->SetActorLocation(Cells[SecondIndex]->GetActorLocation());
		Cells[SecondIndex]->SetActorLocation(temp_loc);
	});
	
	
	Cells.Swap(FirstIndex, SecondIndex);
	
	FPlatformProcess::Sleep(SortSpeed);
	// FGenericPlatformProcess::Sleep(0.5f);
	//FGenericPlatformProcess::Sleep(0.5f);
	//APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	//if (MyPlayer != NULL)
	//{
		
		
	//}
	
	//FLatentActionInfo()
	
	//UKismetSystemLibrary::Delay(this,5.f,)
		
}

