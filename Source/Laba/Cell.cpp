// Fill out your copyright notice in the Description page of Project Settings.

#include "Cell.h"
#include "Materials/MaterialExpressionConstant3Vector.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACell::ACell()
{
	PrimaryActorTick.bCanEverTick = false;
	
	
	//Material = NewObject<UMaterial>();
	
	//static ConstructorHelpers::FObjectFinder<UMaterial> Static_material(
	//	TEXT("Material'/Game/Cell/Cell_Material.Cell_Material'"));

	//Material = Static_material.Object;

	
	//Material = CreateDefaultSubobject<UMaterial>(TEXT("Material"));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	//Mesh->SetMaterial(0, Material);
	
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
	
	
	
	//
}

// Called every frame

