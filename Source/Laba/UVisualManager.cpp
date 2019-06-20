// Fill out your copyright notice in the Description page of Project Settings.


/**

  UVisualManager.cpp

  Purpose: file with main functions

 */

#include "UVisualManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GenericPlatformProcess.h"
#include "Async.h"
#include "Future.h"
#include "ThreadManager.h"
//just a macros for more comfortable Debug
#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

UVisualManager::UVisualManager() 
{
	static ConstructorHelpers::FObjectFinder<UClass> Cell_BP_temp(
		TEXT("Class'/Game/Cell/BP_Cell.BP_Cell_C'"));
	if(Cell_BP_temp.Object)
		Cell_BP = Cell_BP_temp.Object;
	//searchs BP_Cell and if finds, sets Cell_BP

	ComparesNum = AssignmentsNum = 0;

	bIsSorted = false;
}


//Singleton, it is partially set by the code, and partly by the editor of the propeller
UVisualManager* UVisualManager::GetVisualManager()
{
	UVisualManager* DataInstance = Cast<UVisualManager>(GEngine->GameSingleton);

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	return DataInstance;
}

void UVisualManager::SpawnCells()
{
	ComparesNum = ComparesNum = 0;
	FVector SpawnPosition(390.000000, -240.000000,  130.000000);//Методом тику знайдена зручне місце для початку спавна
	for (int i = 0; i < Height;++i , SpawnPosition+=FVector(0,-25.f*Length,-25.f))//Звиг по вертикалі
		for (int j = 0; j < Length; ++j, SpawnPosition+=FVector(0,25.f,0))//Здвиг по горизонталі
		{
			//Here cells are spawning and added to array Cells. And assignment of nums (rand)
			ACell* SpawnedCell = GEngine->GameViewport->GetWorld()->SpawnActor<ACell>(Cell_BP, SpawnPosition, FRotator::ZeroRotator);
			SpawnedCell->InitNum(FMath::RandRange(0,360));//Comfortable for HSV, but it does not matter how many

			Cells.Add(SpawnedCell);
		}
}
//Destruction of cells
void UVisualManager::DestroyCells()
{//можна я ось це все поясню в живу, тут була проблема, рішення інше не знайшов
	//An additional stream is created that waits until the sorting is stopped (the main one can not be used, it partially participates there, otherwise it is elevated)
	bIsSorted = false;
	Async<void>(EAsyncExecution::Thread, [this]()
	{
		bContinueSorting = false;//stopping sorting
		IsSortingOver.Wait();//waiting to stop
		
		AsyncTask(ENamedThreads::GameThread, [this]()//only main flow can edit Unreal essences
		{
			for (int i = 0; i < Cells.Num(); ++i)
				Cells[i]->Destroy();

			Cells.Empty();
		});
	});
}



//It is determined which sorting it is, and the additional stream is started, in order that we see the output and everything is not frozen
void UVisualManager::StartVisualization()
{
	//IsSortingOver = false;
	bIsSorted = false;
	bContinueSorting = true;
	IsSortingOver = Async<void>(EAsyncExecution::Thread, [this]()
	{
		switch (CurrentSort)
		{
		case ESortType::Bubble:
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
		case ESortType::Merge:
			MergeSort(0, Cells.Num() - 1);
			break;
		case ESortType::Bucket:
			BucketSort();
			break;
		}
	});
}

void UVisualManager::BubbleSort()
{
	for (int32 i=0; Less(i , Cells.Num() - 1) && bContinueSorting; i++)
	{
		for (int32 j=0; Less(j , Cells.Num() - i - 1) && bContinueSorting; j++)
			if (More( Cells[j] , Cells[j + 1]))
				VSwap(j, j + 1);
	}
	if (bContinueSorting) bIsSorted = true;
}

void UVisualManager::InsertionSort()
{
	int i, j;
	for (i = 1; Less(i,Cells.Num()); i++) {
		j = i;
		while (More(j,0) && More(Cells[j - 1], Cells[j]) && bContinueSorting) {
			VSwap(j, j - 1);
			j--;
		}
	}
	if (bContinueSorting) bIsSorted = true;
}

void UVisualManager::QuickSort(int32 left,int32 right)
{
	int32 i = left, j = right;
	int32 pivot = Cells[(left + right) / 2]->GetNum();

	while (LessEq(i,j) && bContinueSorting) {
		while (Less( Cells[i]->GetNum(), pivot))
			i++;
		while (More( Cells[j]->GetNum(), pivot))
			j--;
		if (LessEq(i,j)) {
			VSwap(i, j);
			i++;
			j--;
		}
	};

	if (Less(left,j)  && bContinueSorting)
		QuickSort( left, j);
	if (Less(i, right) && bContinueSorting)
		QuickSort( i, right);
	if (bContinueSorting && left==0 && right==Cells.Num()-1) bIsSorted = true;
}
//Like Insertion sort but a bit different
void UVisualManager::GnomeSort()
{
	for (int32 i = 0; Less(i + 1 , Cells.Num()) && bContinueSorting; ++i) {
		if (More(Cells[i],  Cells[i + 1])) {
			VSwap(i, i + 1);
			if (NotEq(i,0))
				i -= 2; 
		}
	}
	if (bContinueSorting) bIsSorted = true;
}

void UVisualManager::MergeSort(int32 l, int32 r)
{
	auto merge = [&](int32 l, int32 m, int32 r){
		int32 i, j, k;
		int32 n1 = m - l + 1;
		int32 n2 = r - m;

		TArray<int32>L, R;
		L.Init(-1,n1); R.Init(-1,n2);
		
		for (i = 0;Less(i,n1) && bContinueSorting; i++)
			L[i] = Cells[l + i]->GetNum();
		for (j = 0;Less(j,n2) && bContinueSorting; j++)
			R[j] = Cells[m + 1 + j]->GetNum();
		i = 0;  j = 0;  k = l; 

		while (Less(i,n1) && Less(j,n2) && bContinueSorting)
		{
			if (LessEq(L[i],R[j]))
			{
				VAssign(k, L[i]);
				i++;
			}
			else
			{
				VAssign(k, R[j]);
				j++;
			}
			k++;
		}
		while (Less(i,n1) && bContinueSorting)
		{
			VAssign(k, L[i]);
			i++;
			k++;
		}
		while (Less(j,n2) && bContinueSorting)
		{
			VAssign(k, R[j]);
			j++;
			k++;
		}
	};

	if (Less( l , r))
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int32 m = l + (r - l) / 2;

		// Sort first and second halves 
		if (bContinueSorting)
		{
			MergeSort(l, m);
			MergeSort(m + 1, r);

			merge(l, m, r);
		}
	}
	if (bContinueSorting) bIsSorted = true;
}

void UVisualManager::BucketSort()
{
	/////////////////////////////////////
	const float All_Num = 370;
	
	auto GnSort = [&](TArray<int32>arr){
		for (int32 i = 0; Less(i + 1, arr.Num()) && bContinueSorting; ++i) {
			if (More(arr[i], arr[i + 1])) {
				DSwap(arr[i], arr[i + 1]);
				if (NotEq(i,0))
					i -= 2;
			}
		}
	};
	/////////////////////////////////////

	TArray< TArray<int32> >b;
	b.Init(TArray<int32>(), Cells.Num());
	
	for (int32 i = 0; Less( i , Cells.Num()) && bContinueSorting; i++)
	{
		int32 bi = Cells.Num() * (float(Cells[i]->GetNum())/All_Num); // Index in bucket 
		b[bi].Push(Cells[i]->GetNum());
	}

	for (int32 i = 0;Less(i,Cells.Num()) && bContinueSorting; i++)
		GnSort(b[i]);

	// 4) Concatenate all buckets into arr[] 
	int32 index = 0;
	for (int32 i = 0;Less(i,Cells.Num()) && bContinueSorting; i++)
		for (int32 j = 0; Less(j,b[i].Num()) && bContinueSorting; j++)
		{
			VAssign(index, b[i][j]);
			//Cells[index] = b[i][j];
			++index;
		}
	if (bContinueSorting) bIsSorted = true;
}

void UVisualManager::DSwap(int32& a, int32& b)
{
	int32 t = a;
	a = b;
	b = t;
	AssignmentsNum += 3;
}

//My VSwap, to change the position of the vectors on the screen
void UVisualManager::VSwap(int32 FirstIndex,  int32 SecondIndex)
{
	//Проблема в тому, що я НІЯК не можу дізнатися влаштовуваними методами, коли AsyncTask закінчиться, довелося створювати свої TFuture і TPromise
	TFuture<void>IsSwapped;
	TPromise<void>SetIsSwapped;
	IsSwapped = SetIsSwapped.GetFuture();

	//Тільки головний потік може редагувати Анріаловські Сутності
	AsyncTask(ENamedThreads::GameThread, [&](){
		//Swap actors positions
		FVector temp_loc = Cells[FirstIndex]->GetActorLocation();
		Cells[FirstIndex]->SetActorLocation(Cells[SecondIndex]->GetActorLocation());
		Cells[SecondIndex]->SetActorLocation(temp_loc);

		SetIsSwapped.SetValue();
	});
	//Delay with help of SortSpeed
	FPlatformProcess::Sleep(SortSpeed);
	//We are waiting for the Main flow to finish its business, because in small delays, it can work slower than this flow and there will be GIGANT problems
	IsSwapped.Wait();
	AssignmentsNum+=3;
 	Cells.Swap(FirstIndex, SecondIndex);//Свап елементів в масиві
}

void UVisualManager::VAssign(int32 Index, int32 Val)
{
	TFuture<void>IsAssigned;
	TPromise<void>SetIsAssigned;
	IsAssigned = SetIsAssigned.GetFuture();

	//Тільки головний потік може редагувати Анріаловські Сутності
	AsyncTask(ENamedThreads::GameThread, [&]() {
		//Swap actors positions
		Cells[Index]->InitNum(Val);
		SetIsAssigned.SetValue();
	});
	//Delay with help of SortSpeed
	FPlatformProcess::Sleep(SortSpeed/3);
	//We are waiting for the Main flow to finish its business, because in small delays, it can work slower than this flow and there will be GIGANT problems
	IsAssigned.Wait();
	++AssignmentsNum;
	//Cells.Swap(FirstIndex, SecondIndex);//Свап елементів в масиві
}

