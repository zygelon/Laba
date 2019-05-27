// Fill out your copyright notice in the Description page of Project Settings.

/**

  Cell.h

  Purpose: sets values for cells

 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Components/TextRenderComponent.h"
#include "Cell.generated.h"

UCLASS(Blueprintable, BlueprintType)
class LABA_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACell();

	

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cell")
	//UMaterialInterface* Material;
	

protected:
	/*
	* Called when the game starts or when spawned
	*
	* @brief BeginPlay
	*/
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cell")//це краще в живу пояснити, всі макроси - частина анріала
	int32 Number;//the number of the element in the array for which I am sorting

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	UStaticMeshComponent* Mesh;//3D model, that will be on screen, initiallization in BP_Cell

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly, Category = "Cell")
	UTextRenderComponent* NumberAtActor;//Text, which is attached to Actor, and is a Number

public:	
	// Called every frame
	UFUNCTION(BlueprintNativeEvent)
	/*
	* Assigns Number=Num, expands in BP_Cell
	*
	*@brief InitNum
	*/
	 void InitNum(int32 Num);//Присоює Number=Num, розширюється в BP_Cell

	UFUNCTION(BlueprintCallable)
	int32 const GetNum() { return Number; }//just a getter

};
