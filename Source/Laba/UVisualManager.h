// Fill out your copyright notice in the Description page of Project Settings.

/**

  UVisualManager.h

  Purpose: file with main functions

 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Engine/TextRenderActor.h"
#include "Future.h"
#include "UVisualManager.generated.h"



UENUM(BlueprintType)		//types of sorts
enum class ESortType : uint8
{
	Bubble,
	Insertion,
	Gnome,
	Quick,
	Merge,
	Bucket
};

//very terrible class

UCLASS()
class LABA_API UVisualManager : public UObject
{
	GENERATED_BODY()
	friend class AExasss;
	friend class ADestroyTest;
	friend class AMenuTest;
	friend class ALengthTest;
public:
	UFUNCTION(BlueprintPure, Category = "Singleton")
	static UVisualManager* GetVisualManager(); //Singletone
	
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	/*
	*Creates cells, exactly as much as the user has specified.
	*
	*@brief SpawnCells
	*/
	void SpawnCells();

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	/*
	*Destroys all cells, executed when returning to the menu.
	*
	*@brief DestroyCells
	*/
	void DestroyCells();

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Height;//Obviously, the number of cells in height

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Length;//same but horizontally

	UPROPERTY( BlueprintReadWrite, Category = "CurrentSort")
	/*
	*Obvious
	*
	*@brief SortSpeed
	*/
	float SortSpeed;

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	/*
	*Specifies the sort type for the class
	*
	*@brief SetSortType
	*/
	void SetSortType(ESortType Sort) { CurrentSort = Sort; }

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	/*
	*returns the type of sort
	*
	*@brief GetSortType
	*/
	ESortType GetSortType() { return CurrentSort; }

protected:
	

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 AssignmentsNum;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 ComparesNum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cell")
	TSubclassOf<ACell> Cell_BP;//Cell_BP will contain heir from ACell, this is a pointer

	UPROPERTY()
	bool bIsSorted;

	UPROPERTY()
	/*
	*To continue sorting, or to stop, you need to stop the sorting functions
	*
	*@brief bContinueSorting
	*/
	bool bContinueSorting;

	UPROPERTY()
	ESortType CurrentSort;//current sort

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	TArray<ACell*>Cells;// Here are all the cells BP_Cell, which using dynamic
	//polymorphism becoming ACell

	//////////////////////////////////////////////Sorts
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void BubbleSort();

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void InsertionSort();

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void QuickSort(int32 left,int32 right);

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void GnomeSort();

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void MergeSort(int32 l, int32 r);

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void BucketSort();
	//////////////////////////////////////////////
	bool More(ACell* first, ACell* second) { ComparesNum++; return first->GetNum() > second->GetNum(); }
	bool More(int32 first, int32 second) { ComparesNum++; return first > second; }
	bool Less(ACell* first, ACell* second) { ComparesNum++;return first->GetNum() < second->GetNum(); }
	bool Less(int32 first, int32 second) { ComparesNum++; return first < second; }
	bool LessEq(ACell* first, ACell* second) { ComparesNum++; return first->GetNum() <= second->GetNum(); }
	bool LessEq(int32 first, int32 second) { ComparesNum++; return first <= second; }
	bool MoreEq(ACell* first, ACell* second) { ComparesNum++; return first->GetNum() >= second->GetNum(); }
	bool MoreEq(int32 first, int32 second) { ComparesNum++; return first >= second; }
	bool NotEq(int32 first, int32 second) { ComparesNum++; return first != second; }
	bool Equal(int32 first, int32 second) { ComparesNum++; return first == second; }
	//////////////////////////////////////////////

	TFuture<void>IsSortingOver;//Required to stop sorting when moving to MainMenu
	
	UFUNCTION()
	void DSwap(int32& a, int32& b);

	UFUNCTION()
	void VSwap(int32 FirstIndex, int32 SecondIndex);//VSwap changes the location of the elements in Cells and changes their Location on scene
	
	UFUNCTION()
	void VAssign(int32 Index, int32 Val);
public:	
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void StartVisualization();//starting of visualization
private:
	UVisualManager();
};
