// Fill out your copyright notice in the Description page of Project Settings.

#include "Cell.h"
#include "Materials/MaterialExpressionConstant3Vector.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACell::ACell()
{
	PrimaryActorTick.bCanEverTick = false;//вимикається виклик функції, що має кожний кадр викликатися
	//3д модель, задається в спадкоємці BP_Cell
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));//Виклик конструктора(SetDefaultSubobject це такий конструктор)
	SetRootComponent(Mesh);//роблю Mesh головною компонентою

	//Прикріплюю номер до модельки
	NumberAtActor = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");//
	NumberAtActor->SetupAttachment(Mesh);

	NumberAtActor->SetTextRenderColor(FColor::Black);
	NumberAtActor->SetWorldSize(55.f);//обраний методом тика як оптимальний

	NumberAtActor->SetHorizontalAlignment(EHTA_Center);
	NumberAtActor->SetVerticalAlignment(EVRTA_TextCenter);

	NumberAtActor->SetRelativeLocation(FVector(-55.f, 0.f, 0.f));//методом тику, приліпив на куб
	NumberAtActor->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));//щоб зеркально не були цифри
	//NumberAtActor->SetRelativeLocation(FVector());
	//Mesh->SetMaterial(0, Material);
	
}
//Implementation означає, що метод може перевизначатись в спадкоємці - блупринті
void ACell::InitNum_Implementation(int32 Num)
{//очевидно
	Number = Num;
	
	//Даю значення тексту, що показує номер елементу
	NumberAtActor->SetText(FText::FromString(FString::FromInt(Number)));
}

//робить нічого
void ACell::BeginPlay()
{
	Super::BeginPlay();

}



