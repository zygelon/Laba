// Fill out your copyright notice in the Description page of Project Settings.

#include "Cell.h"
#include "Materials/MaterialExpressionConstant3Vector.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Material = NewObject<UMaterial>();

}

void ACell::InitNum(int32 Num)
{
	Number = Num;

	//UMaterialExpressionConstant3Vector* BaseColor =NewObject<UMaterialExpressionConstant3Vector>(Material);

	//BaseColor->Constant = FColor::FromHex(FString::FromInt(Number*10000));

	//Material->
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame

