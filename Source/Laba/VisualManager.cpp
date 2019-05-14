// Fill out your copyright notice in the Description page of Project Settings.

#include "VisualManager.h"
#include "Engine/World.h"

// Sets default values
AVisualManager::AVisualManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UBlueprint> Cell_BP_temp(
		TEXT("Blueprint'/Game/Cell/BP_Cell.BP_Cell'"));

	Cell_BP = Cell_BP_temp.Object->GeneratedClass;
}

void AVisualManager::SpawnCells()
{
	//atic ConstructorHelpers::FObjectFinder<UBlueprint> BP_Cell
	//(TEXT("Blueprint'/Game/Cell/BP_Cell.BP_Cell'"));
	FVector SpawnPosition(390.000000, -240.000000,  130.000000);//spawn position
	for (int i = 0; i < Height;++i, SpawnPosition+=FVector(0,-25.f*Length,-25.f))//50 -size of cell edge
	{
		for (int j = 0; j < Length; ++j, SpawnPosition+=FVector(0,25.f,0))
		{
			
			//FRotator Rotation(0, 0, 0);

			//auto SpawnClass = 
			ACell* SpawnedCell = GetWorld()->SpawnActor<ACell>(Cell_BP, SpawnPosition, FRotator::ZeroRotator);
			SpawnedCell->InitNum(FMath::RandRange(0,360));
			Cells.Add(SpawnedCell);
		}
	}
}

void AVisualManager::DestroyCells()
{
	if (true) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("Memory Error" )));  }

	for (int i = 0; i < Cells.Num(); ++i)
	{
		Cells[i]->Destroy();
	}
	Cells.Empty();
}

void AVisualManager::BeginPlay()
{
	
}

// Called when the game starts or when spawned

// Called every frame


void AVisualManager::Draw()
{

}

