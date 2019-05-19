// Fill out your copyright notice in the Description page of Project Settings.

#include "Cell.h"
#include "Materials/MaterialExpressionConstant3Vector.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACell::ACell()
{
	PrimaryActorTick.bCanEverTick = false;//���������� ������ �������, �� �� ������ ���� �����������
	//3� ������, �������� � ��������� BP_Cell
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));//������ ������������(SetDefaultSubobject �� ����� �����������)
	SetRootComponent(Mesh);//����� Mesh �������� �����������

	//��������� ����� �� ��������
	NumberAtActor = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");//
	NumberAtActor->SetupAttachment(Mesh);

	NumberAtActor->SetTextRenderColor(FColor::Black);
	NumberAtActor->SetWorldSize(55.f);//������� ������� ���� �� �����������

	NumberAtActor->SetHorizontalAlignment(EHTA_Center);
	NumberAtActor->SetVerticalAlignment(EVRTA_TextCenter);

	NumberAtActor->SetRelativeLocation(FVector(-55.f, 0.f, 0.f));//������� ����, ������� �� ���
	NumberAtActor->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));//��� ��������� �� ���� �����
	//NumberAtActor->SetRelativeLocation(FVector());
	//Mesh->SetMaterial(0, Material);
	
}
//Implementation ������, �� ����� ���� ��������������� � ��������� - ��������
void ACell::InitNum_Implementation(int32 Num)
{//��������
	Number = Num;
	
	//��� �������� ������, �� ������ ����� ��������
	NumberAtActor->SetText(FText::FromString(FString::FromInt(Number)));
}

//������ �����
void ACell::BeginPlay()
{
	Super::BeginPlay();

}



