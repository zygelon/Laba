// Fill out your copyright notice in the Description page of Project Settings.

#include "Cell.h"
#include "Materials/MaterialExpressionConstant3Vector.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"

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


	NumberAtActor = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	NumberAtActor->SetupAttachment(Mesh);

	NumberAtActor->SetTextRenderColor(FColor::Black);
	NumberAtActor->SetWorldSize(55.f);

	NumberAtActor->SetHorizontalAlignment(EHTA_Center);
	NumberAtActor->SetVerticalAlignment(EVRTA_TextCenter);

	NumberAtActor->SetRelativeLocation(FVector(-55.f, 0.f, 0.f));
	NumberAtActor->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	//NumberAtActor->SetRelativeLocation(FVector());
	//Mesh->SetMaterial(0, Material);
	
}

void ACell::InitNum_Implementation(int32 Num)
{
	Number = Num;
	
	
	NumberAtActor->SetText(FText::FromString(FString::FromInt(Number)));
	
	//UMaterialExpressionConstant3Vector* BaseColor =NewObject<UMaterialExpressionConstant3Vector>(Material);

	//BaseColor->Constant = FColor::FromHex(FString::FromInt(Number*10000));

	//Material->
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
	
	//FLinearColor rgb;
	//UKismetMathLibrary::HSVToRGB_Vector(, rgb);
	//CreateDynamicMaterialInstance(Mesh, 0, Mesh->GetMaterial(0))->SetVectorParameterValue(InputColor, rgb);
	
	
	//
}

// Called every frame

