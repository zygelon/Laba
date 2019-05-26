// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Engine/TextRenderActor.h"
#include "Future.h"
#include "UVisualManager.generated.h"



UENUM(BlueprintType)		//���� ���������, �� ����������������
enum class ESortType : uint8
{
	Bubble,
	Insertion,
	Gnome,
	Quick
};

//�� ���� �������� ���� � ���� � ����� ������� ���� ���� � �� 2 �����, ��� ���� ����, � � ���� :(

UCLASS()
class LABA_API UVisualManager : public UObject
{
	GENERATED_BODY()
	friend class AExasss;
public:
	UFUNCTION(BlueprintPure, Category = "Singleton")
	static UVisualManager* GetVisualManager(); //ѳ������, ������
	
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void SpawnCells();//������� ������, ���� ������, ������ ����� ����������.

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void DestroyCells();//����� �� ������, ���������� ��� ��������� � ����

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Height;//��������, ������� ����� �� �����

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Length;//��� ���� ��� �� ����������

	UPROPERTY( BlueprintReadWrite, Category = "CurrentSort")
	float SortSpeed;//��������

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	void SetSortType(ESortType Sort) { CurrentSort = Sort; }//���� ��� ���������� ��� �����

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	ESortType GetSortType() { return CurrentSort; }//������� ��� ����������

protected:
	

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 SwapsNum;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 ComparesNum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cell")
	TSubclassOf<ACell> Cell_BP;//Cell_BP ���� ������ ��������� �� ACell, �� ��������(�������)

	UPROPERTY()
	bool bIsSorted;

	UPROPERTY()
	bool bContinueSorting;//������������ ����������, �� ���������, ������� ��� ��������� ������� ����������

	UPROPERTY()
	ESortType CurrentSort;//������� ����������

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	TArray<ACell*>Cells;// ��� ������ �� ������ BP_Cell, �� �� ��������� ����������
	//�����������(��� �� �� �������) ������ ACell

	//////////////////////////////////////////////Sorts
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void BubbleSort();

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void InsertionSort();

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void QuickSort(int32 left,int32 right);

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void GnomeSort();
	//////////////////////////////////////////////
	bool More(ACell* first, ACell* second) { ComparesNum++; return first->GetNum() > second->GetNum(); }
	bool More(int32 first, int32 second) { ComparesNum++; return first > second; }
	bool Less(ACell* first, ACell* second) { ComparesNum++;return first->GetNum() < second->GetNum(); }
	bool Less(int32 first, int32 second) { ComparesNum++; return first < second; }
	bool LessEq(ACell* first, ACell* second) { ComparesNum++; return first->GetNum() <= second->GetNum(); }
	bool LessEq(int32 first, int32 second) { ComparesNum++; return first <= second; }
	bool MoreEq(ACell* first, ACell* second) { ComparesNum++; return first->GetNum() >= second->GetNum(); }
	bool MoreEq(int32 first, int32 second) { ComparesNum++; return first >= second; }
	//////////////////////////////////////////////

	TFuture<void>IsSortingOver;//�������, ��� ��������� ����������, �� ��� �������� �� MainMenu
	

	UFUNCTION()
	void VSwap(int32 FirstIndex, int32 SecondIndex);//��� ��� ���� ���������� �� �������� ���. VSwap ����� ������������ �������� � Cells �� ���� �� Location �� ����

public:	
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void StartVisualization();//� ����� ���������� ��� ����������
private:
	UVisualManager();
};
