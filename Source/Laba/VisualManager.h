// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Engine/TextRenderActor.h"
#include "Future.h"
#include "VisualManager.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ESortType : uint8
{
	Bubble,
	Insertion,
	Gnome,
	Quick
};

UCLASS()
class LABA_API AVisualManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisualManager();
	
	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void SpawnCells();

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void DestroyCells();

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Height;

	UPROPERTY( BlueprintReadWrite, Category = "Size")
	int32 Length;

	UPROPERTY( BlueprintReadWrite, Category = "CurrentSort")
	float SortSpeed;

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	void SetSortType(ESortType Sort) { CurrentSort = Sort; }

	UFUNCTION(BlueprintCallable, Category = "CurrentSort")
	ESortType GetSortType() { return CurrentSort; }
	//
	void TurnOff() {
		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		if (MyPlayer != NULL)
		{
			MyPlayer->SetPause(false);
			//GetWorldTimerManager().SetTimer(VTimer, [this] {MyPlayer->SetPause(false)}, false, 1.f, 1.f);
		}
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cell")
	TSubclassOf<ACell> Cell_BP;

	UPROPERTY()
	bool bContinueSorting;

	UPROPERTY()
	ESortType CurrentSort;

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	TArray<ACell*>Cells;
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
	//UCLASS()
	TFuture<void>IsSortingOver;

	UFUNCTION()
	void VSwap(int32 FirstIndex, int32 SecondIndex);

public:	
	// Called every frame

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void StartVisualization();
};
