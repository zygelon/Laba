// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Engine/TextRenderActor.h"
#include "Future.h"
#include "UVisualManager.generated.h"



UENUM(BlueprintType)		//Типи сортувань, що використовуються
enum class ESortType : uint8
{
	Bubble,
	Insertion,
	Gnome,
	Quick
};

//Це дуже страшний клас і було б добре розбити його хоча б на 2 класи, але часу мало, а я один :(

UCLASS()
class LABA_API UVisualManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Singleton")
	static UVisualManager* GetVisualManager(); //Сінглтон, просто
	
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void SpawnCells();//Створює клітини, рівно стільки, скільки задав користувач.

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void DestroyCells();//Знищує всі клітини, виконується при поверненні в меню

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Height;//Очевидно, кількість клітин по висоті

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Length;//теж саме але по горизонталі

	UPROPERTY( BlueprintReadWrite, Category = "CurrentSort")
	float SortSpeed;//Очевидно

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	void SetSortType(ESortType Sort) { CurrentSort = Sort; }//Задає вид сортування для класу

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	ESortType GetSortType() { return CurrentSort; }//Повертає вид сортування

protected:
	

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 SwapsNum;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 ComparesNum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cell")
	TSubclassOf<ACell> Cell_BP;//Cell_BP буде містити спадкоємця від ACell, це вказівник(здається)

	UPROPERTY()
	bool bContinueSorting;//Продовжувати сортування, чи припинити, потрібно для зупинення функцій сортування

	UPROPERTY()
	ESortType CurrentSort;//поточна сортировка

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	TArray<ACell*>Cells;// Тут лежать всі клітини BP_Cell, які за допомогою динамічного
	//поліморфізму(або як це назвати) стають ACell

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

	TFuture<void>IsSortingOver;//Потрібно, щоб припинити сортування, під час переходу до MainMenu
	

	UFUNCTION()
	void VSwap(int32 FirstIndex, int32 SecondIndex);//тут вся суть візуалізації та страшний код. VSwap зімнює розташування елементів в Cells та міняє хз Location на сцені

public:	
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void StartVisualization();//З цього починається вся візуалізація
private:
	UVisualManager();
};
