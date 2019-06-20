// Fill out your copyright notice in the Description page of Project Settings.


/**

  UIMemento.h

  Purpose: Sets default values

 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIMemento.generated.h"

UCLASS(BlueprintType)
class LABA_API UUIMemento : public UObject
{
	GENERATED_BODY()
		
	
public:	
	UUIMemento();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Height;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Length;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	float SortSpeed;
public:	
	UFUNCTION(BlueprintCallable)
	/*
	* gets height
	*
	* @brief GetHeight
	*/
	int32 GetHeight() { return Height; }

	UFUNCTION(BlueprintCallable)
	/*
	* gets length
	*
	* @brief GetLength
	*/
	int32 GetLength() { return Length; }

	UFUNCTION(BlueprintCallable)
	/*
	* sets height
	*
	* @brief SetHeight
	*/
	void SetHeight( int32 _Height) { this->Height = _Height; }
	UFUNCTION(BlueprintCallable)
	/*
	* sets length
	*
	* @brief SetLength
	*/
	void SetLength( int32 _Length) { this->Length = _Length; }
	UFUNCTION(BlueprintCallable)
	/*
	* sets Sort speed
	*
	* @brief SetSortSpeed
	*/
	void SetSortSpeed(float _SortSpeed) { this->SortSpeed = _SortSpeed; }


};
