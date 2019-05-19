// Fill out your copyright notice in the Description page of Project Settings.

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cell")//�� ����� � ���� ��������, �� ������� - ������� ������
	int32 Number;//����� ��������, � �����, ��� ����� �������� ����������

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	UStaticMeshComponent* Mesh;//�������� 3�, �� ���� �� �����, � BP_Cell �����������

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly, Category = "Cell")
	UTextRenderComponent* NumberAtActor;//�����, �� �������� �� Actor, �� �� �������� Number

public:	
	// Called every frame
	UFUNCTION(BlueprintNativeEvent)
	 void InitNum(int32 Num);//������� Number=Num, ������������ � BP_Cell

	UFUNCTION(BlueprintCallable)
	int32 GetNum() { return Number; }//������ ����� :)

};
