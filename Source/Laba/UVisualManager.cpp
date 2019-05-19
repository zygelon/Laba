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
	for (int32 i=0; i < Cells.Num() - 1 && bContinueSorting; i++)
	{
		for (int32 j=0; j < Cells.Num() - i - 1 && bContinueSorting; j++)
			if (Cells[j]->GetNum() > Cells[j + 1]->GetNum())
			{
				//GetWorldTimerManager().SetTimer(VTimer, .f, false, 20.f,);
				VSwap(j, j + 1);
			}
	}
}

void UVisualManager::InsertionSort()
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

void UVisualManager::QuickSort(int32 left,int32 right)
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
//����� �� Insertion sort ��� ����� �����������
void UVisualManager::GnomeSort()
{
	for (int32 i = 0; i + 1 < Cells.Num() && bContinueSorting; ++i) {
		if (Cells[i]->GetNum() > Cells[i + 1]->GetNum()) {
			VSwap(i, i + 1);
			if (i != 0)
				i -= 2; 
		}
	}
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
 	Cells.Swap(FirstIndex, SecondIndex);//���� �������� � �����
	
}

