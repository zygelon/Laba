// Fill out your copyright notice in the Description page of Project Settings.

#include "UVisualManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GenericPlatformProcess.h"
#include "Async.h"
#include "Future.h"
#include "ThreadManager.h"
//просто макрос для більш зручного Debug
#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

UVisualManager::UVisualManager() 
{
	static ConstructorHelpers::FObjectFinder<UClass> Cell_BP_temp(
		TEXT("Class'/Game/Cell/BP_Cell.BP_Cell_C'"));
	if(Cell_BP_temp.Object)
		Cell_BP = Cell_BP_temp.Object;
	//шукає BP_Cell та якщо знаходить, задає Cell_BP

	bIsSorted = false;
}


//Singleton, він частково задається кодом, а частково в редакторі рушія
UVisualManager* UVisualManager::GetVisualManager()
{
	UVisualManager* DataInstance = Cast<UVisualManager>(GEngine->GameSingleton);

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	return DataInstance;
}
//тут потрібно позбутися від магічних чисел, але я не встиг:(
void UVisualManager::SpawnCells()
{
	ComparesNum = SwapsNum = 0;
	FVector SpawnPosition(390.000000, -240.000000,  130.000000);//Методом тику знайдена зручне місце для початку спавна
	for (int i = 0; i < Height;++i , SpawnPosition+=FVector(0,-25.f*Length,-25.f))//Звиг по вертикалі
		for (int j = 0; j < Length; ++j, SpawnPosition+=FVector(0,25.f,0))//Здвиг по горизонталі
		{
			//Тут відбувається спаун клітин, та додавання їх до масиву Cells. Ну і задання числа елемента(рандом)
			ACell* SpawnedCell = GEngine->GameViewport->GetWorld()->SpawnActor<ACell>(Cell_BP, SpawnPosition, FRotator::ZeroRotator);
			SpawnedCell->InitNum(FMath::RandRange(0,360));//Зручно для HSV, але не має значення до скількох

			Cells.Add(SpawnedCell);
		}
}
//Знищення клітин. Обережно дуже страшний код.
void UVisualManager::DestroyCells()
{//можна я ось це все поясню в живу, тут була проблема, рішення інше не знайшов
	//Створюється доп потік, що чекає, поки припинеться сортування(основний не можна використовувати, він там частково приймає участь, інакше підвисне)
	bIsSorted = false;
	Async<void>(EAsyncExecution::Thread, [this]()
	{
		bContinueSorting = false;//зупиняємо сортування
		IsSortingOver.Wait();//чекаємо поки зупинеться
		
		AsyncTask(ENamedThreads::GameThread, [this]()//тільки головний потік може редагувати Анріаловські Сутності
		{
			for (int i = 0; i < Cells.Num(); ++i)
				Cells[i]->Destroy();

			Cells.Empty();
		});
	});
}



//Визначається, що за сортування, та запускається доп. потік, для того, щоб ми бачили вивід і все не застигло
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
//Схожа на Insertion sort але трохи відрізняється
void UVisualManager::GnomeSort()
{
	for (int32 i = 0; Less(i + 1 , Cells.Num()) && bContinueSorting; ++i) {
		if (More(Cells[i],  Cells[i + 1])) {
			VSwap(i, i + 1);
			if (i != 0)
				i -= 2; 
		}
	}
	if (bContinueSorting) bIsSorted = true;
}
//Трохи страшний код. Мій VSwap, щоб змінювати позиції екторів на екрані
void UVisualManager::VSwap(int32 FirstIndex,  int32 SecondIndex)
{
	//Проблема в тому, що я НІЯК не можу дізнатися влаштовуваними методами, коли AsyncTask закінчиться, довелося створювати свої TFuture і TPromise
	TFuture<void>IsSwapped;
	TPromise<void>SetIsSwapped;
	IsSwapped = SetIsSwapped.GetFuture();

	//Тільки головний потік може редагувати Анріаловські Сутності
	AsyncTask(ENamedThreads::GameThread, [&](){
		//Swap позицій акторів
		FVector temp_loc = Cells[FirstIndex]->GetActorLocation();
		Cells[FirstIndex]->SetActorLocation(Cells[SecondIndex]->GetActorLocation());
		Cells[SecondIndex]->SetActorLocation(temp_loc);

		SetIsSwapped.SetValue();
	});
	//Затримка, що задається за допомогою SortSpeed, назва трохи некоректна
	FPlatformProcess::Sleep(SortSpeed);
	//Чекаємо поки Головний потік закінчить свої справи, бо на малих затримках він може працювати повільніше ніж цей потік і будуть ГІГАНСЬКІ проблеми
	IsSwapped.Wait();
	++SwapsNum;
 	Cells.Swap(FirstIndex, SecondIndex);//Свап елементів в масиві
}

