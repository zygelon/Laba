// Fill out your copyright notice in the Description page of Project Settings.

#include "VisualManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GenericPlatformProcess.h"
#include "Async.h"
#include "Future.h"
#include "ThreadManager.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

// Sets default values
AVisualManager::AVisualManager() 
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
	for (int i = 0; i < Height;++i , SpawnPosition+=FVector(0,-25.f*Length,-25.f))//50 -size of cell edge
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
	Async<void>(EAsyncExecution::Thread, [this]()
	{
		bContinueSorting = false;
		IsSortingOver.Wait();
		//if (true) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			//FString::Printf(TEXT("Memory Error" )));  }
		AsyncTask(ENamedThreads::GameThread, [this]()
		{
			for (int i = 0; i < Cells.Num(); ++i)
				Cells[i]->Destroy();

			Cells.Empty();
		});
	});
}

void AVisualManager::BeginPlay()
{
	
}


void AVisualManager::StartVisualization()
{
	bContinueSorting = true;
	IsSortingOver = Async<void>(EAsyncExecution::Thread, [this]()
	{
		switch (CurrentSort)
		{
		case ESortType::Bubble:
			//Async<int>(EAsyncExecution::ThreadPool, [this]() {BubbleSort(); return 1; });
			BubbleSort();
			break;
		case ESortType::Insertion:
			InsertionSort();
			break;
		case ESortType::Gnome:
			GnomeSort();
			break;
		case ESortType::Quick:
			QuickSort(0, Cells.Num() - 1);
			break;
		}
	});
}

void AVisualManager::BubbleSort()
{
	for (int32 i=0; i < Cells.Num() - 1 && bContinueSorting; i++)
	{
		for (int32 j=0; j < Cells.Num() - i - 1 && bContinueSorting; j++)
			if (Cells[j]->GetNum() > Cells[j + 1]->GetNum())
			{
				//GetWorldTimerManager().SetTimer(VTimer, .f, false, 20.f,);
				VSwap(j, j + 1);
			}
	}
	//bIsSorted = true;
}

void AVisualManager::InsertionSort()
{
	int i, j;
	for (i = 1; i < Cells.Num(); i++) {
		j = i;
		while (j > 0 && Cells[j - 1]->GetNum() > Cells[j]->GetNum() && bContinueSorting) {
			VSwap(j, j - 1);
			j--;
		}
	}
}

void AVisualManager::QuickSort(int32 left,int32 right)
{
	int32 i = left, j = right;
	int32 pivot = Cells[(left + right) / 2]->GetNum();

	while (i <= j && bContinueSorting) {
		while (Cells[i]->GetNum() < pivot)
			i++;
		while (Cells[j]->GetNum() > pivot)
			j--;
		if (i <= j) {
			VSwap(i, j);
			i++;
			j--;
		}
	};

	if (left < j && bContinueSorting)
		QuickSort( left, j);
	if (i < right && bContinueSorting)
		QuickSort( i, right);
}

void AVisualManager::GnomeSort()
{
	for (int32 i = 0; i + 1 < Cells.Num() && bContinueSorting; ++i) {
		if (Cells[i]->GetNum() > Cells[i + 1]->GetNum()) {
			VSwap(i, i + 1);
			if (i != 0)
				i -= 2; 
		}
	}
}

void AVisualManager::VSwap(int32 FirstIndex,  int32 SecondIndex)
{
	//D(FThreadManager::Get().GetThreadName(ThreadId));

	TFuture<void>IsSwapped;
	TPromise<void>SetIsSwapped;
	IsSwapped = SetIsSwapped.GetFuture();

	//UE_LOG()
	AsyncTask(ENamedThreads::GameThread, [&](){
		FVector temp_loc = Cells[FirstIndex]->GetActorLocation();
		Cells[FirstIndex]->SetActorLocation(Cells[SecondIndex]->GetActorLocation());
		Cells[SecondIndex]->SetActorLocation(temp_loc);

		//D(FThreadManager::Get().GetThreadName(ThreadId));
		SetIsSwapped.SetValue();
	});

	FPlatformProcess::Sleep(SortSpeed);
	IsSwapped.Wait();
 	Cells.Swap(FirstIndex, SecondIndex);
	
}

