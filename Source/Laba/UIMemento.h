// Fill out your copyright notice in the Description page of Project Settings.

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
	void SetHeight( int32 _Length) { this->Length = _Length; }
	UFUNCTION(BlueprintCallable)
	void SetLength( int32 _Height) { this->Height = _Height; }
	UFUNCTION(BlueprintCallable)
	void SetSortSpeed(float _SortSpeed) { this->SortSpeed = _SortSpeed; }


};
