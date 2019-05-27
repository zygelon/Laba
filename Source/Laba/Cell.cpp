// Fill out your copyright notice in the Description page of Project Settings.

/**

  Cell.cpp

  Purpose: sets values for cells

 */

#include "Cell.h"
#include "Materials/MaterialExpressionConstant3Vector.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACell::ACell()
{
	PrimaryActorTick.bCanEverTick = false;//the function call that each frame is called is turned off
	//3d model, given in the heir BP_Cell
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));//call of constructor (SetDefaultSubobject this is a constructor)
	SetRootComponent(Mesh);//making Mesh the main component

	//Attaching a number to model
	NumberAtActor = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");//
	NumberAtActor->SetupAttachment(Mesh);

	NumberAtActor->SetTextRenderColor(FColor::Black);
	NumberAtActor->SetWorldSize(55.f);//choosed as optimal

	NumberAtActor->SetHorizontalAlignment(EHTA_Center);
	NumberAtActor->SetVerticalAlignment(EVRTA_TextCenter);

	NumberAtActor->SetRelativeLocation(FVector(-55.f, 0.f, 0.f));//dipped on cube
	NumberAtActor->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));//to not mirror the numbers
	//NumberAtActor->SetRelativeLocation(FVector());
	//Mesh->SetMaterial(0, Material);
	
}
//Implementation means that the method can be redefined in the heir - blueprint
void ACell::InitNum_Implementation(int32 Num)
{//очевидно
	Number = Num;
	
	//I give the value of the text that shows the element number
	NumberAtActor->SetText(FText::FromString(FString::FromInt(Number)));
}

//makes nothing
void ACell::BeginPlay()
{
	Super::BeginPlay();

}



