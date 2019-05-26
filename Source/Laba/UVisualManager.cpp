// Fill out your copyright notice in the Description page of Project Settings.

#include "UVisualManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GenericPlatformProcess.h"
#include "Async.h"
#include "Future.h"
#include "ThreadManager.h"
//������ ������ ��� ���� �������� Debug
#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

UVisualManager::UVisualManager() 
{
	static ConstructorHelpers::FObjectFinder<UClass> Cell_BP_temp(
		TEXT("Class'/Game/Cell/BP_Cell.BP_Cell_C'"));
	if(Cell_BP_temp.Object)
		Cell_BP = Cell_BP_temp.Object;
	//���� BP_Cell �� ���� ���������, ���� Cell_BP

	bIsSorted = false;
}


//Singleton, �� �������� �������� �����, � �������� � �������� �����
UVisualManager* UVisualManager::GetVisualManager()
{
	UVisualManager* DataInstance = Cast<UVisualManager>(GEngine->GameSingleton);

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	return DataInstance;
}
//��� ������� ��������� �� ������� �����, ��� � �� �����:(
void UVisualManager::SpawnCells()
{
	ComparesNum = SwapsNum = 0;
	FVector SpawnPosition(390.000000, -240.000000,  130.000000);//������� ���� �������� ������ ���� ��� ������� ������
	for (int i = 0; i < Height;++i , SpawnPosition+=FVector(0,-25.f*Length,-25.f))//���� �� ��������
		for (int j = 0; j < Length; ++j, SpawnPosition+=FVector(0,25.f,0))//����� �� ����������
		{
			//��� ���������� ����� �����, �� ��������� �� �� ������ Cells. �� � ������� ����� ��������(������)
			ACell* SpawnedCell = GEngine->GameViewport->GetWorld()->SpawnActor<ACell>(Cell_BP, SpawnPosition, FRotator::ZeroRotator);
			SpawnedCell->InitNum(FMath::RandRange(0,360));//������ ��� HSV, ��� �� �� �������� �� �������

			Cells.Add(SpawnedCell);
		}
}
//�������� �����. �������� ���� �������� ���.
void UVisualManager::DestroyCells()
{//����� � ��� �� ��� ������ � ����, ��� ���� ��������, ������ ���� �� �������
	//����������� ��� ����, �� ����, ���� ����������� ����������(�������� �� ����� ���������������, �� ��� �������� ������ ������, ������ �������)
	bIsSorted = false;
	Async<void>(EAsyncExecution::Thread, [this]()
	{
		bContinueSorting = false;//��������� ����������
		IsSortingOver.Wait();//������ ���� ����������
		
		AsyncTask(ENamedThreads::GameThread, [this]()//����� �������� ���� ���� ���������� ���������� �������
		{
			for (int i = 0; i < Cells.Num(); ++i)
				Cells[i]->Destroy();

			Cells.Empty();
		});
	});
}



//�����������, �� �� ����������, �� ����������� ���. ����, ��� ����, ��� �� ������ ���� � ��� �� ��������
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
//����� �� Insertion sort ��� ����� �����������
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
//����� �������� ���. ̳� VSwap, ��� �������� ������� ������ �� �����
void UVisualManager::VSwap(int32 FirstIndex,  int32 SecondIndex)
{
	//�������� � ����, �� � Ͳ�� �� ���� �������� �������������� ��������, ���� AsyncTask ����������, �������� ���������� ��� TFuture � TPromise
	TFuture<void>IsSwapped;
	TPromise<void>SetIsSwapped;
	IsSwapped = SetIsSwapped.GetFuture();

	//ҳ���� �������� ���� ���� ���������� ���������� �������
	AsyncTask(ENamedThreads::GameThread, [&](){
		//Swap ������� ������
		FVector temp_loc = Cells[FirstIndex]->GetActorLocation();
		Cells[FirstIndex]->SetActorLocation(Cells[SecondIndex]->GetActorLocation());
		Cells[SecondIndex]->SetActorLocation(temp_loc);

		SetIsSwapped.SetValue();
	});
	//��������, �� �������� �� ��������� SortSpeed, ����� ����� ����������
	FPlatformProcess::Sleep(SortSpeed);
	//������ ���� �������� ���� �������� ��� ������, �� �� ����� ��������� �� ���� ��������� �������� �� ��� ���� � ������ ò�����ʲ ��������
	IsSwapped.Wait();
	++SwapsNum;
 	Cells.Swap(FirstIndex, SecondIndex);//���� �������� � �����
}

