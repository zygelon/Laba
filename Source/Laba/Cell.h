// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Cell.generated.h"

UCLASS(Blueprintable, BlueprintType)
class LABA_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();

	UPROPERTY( VisibleAnywhere,BlueprintReadWrite  ,Category="Cell")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cell")
	UMaterialInterface* Material;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cell")
	int32 Number;
public:	
	// Called every frame
	UFUNCTION(BlueprintCallable)
	virtual void InitNum(int32 Num);

	UFUNCTION(BlueprintCallable)
	int32 GetNum() { return Number; }

};
