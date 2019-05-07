// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabaGameModeBase.generated.h"
/**
 * 
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ESortType : uint8
{
	Bubble,
	Insertion
};

UCLASS()
class LABA_API ALabaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="CurrentSort")
	void SetSortType(ESortType Sort) { CurrentSort = Sort; }

	UFUNCTION(BlueprintCallable, Category="CurrentSort")
	ESortType GetSortType() { return CurrentSort; }

protected:
	UPROPERTY()
	ESortType CurrentSort;
};
