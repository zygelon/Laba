// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "VisualManager.generated.h"

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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
		int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
		int32 Length;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cell")
	TSubclassOf<class ACell> Cell_BP;

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	TArray<  ACell*>Cells;
public:	
	// Called every frame

	UFUNCTION(BlueprintCallable, Category = "Visualization")
	void Draw();
};
