// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrayManagerC.h"
#include "TmpCubeC.h"
#include "Chaos/Collision/CollisionApplyType.h"

// Sets default values
AArrayManagerC::AArrayManagerC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FVector AArrayManagerC::GeneratePosition()
{
	const FVector CubePosition(rand() % 1000 + 1.f, rand() % 1000 + 1.f, rand() % 1000 + 1);
	return CubePosition;
	
}

FRotator AArrayManagerC::GenerateRotation()
{
	const FRotator CubeRotation(0.f, 0.f, 0.f);
	return CubeRotation;
}

void AArrayManagerC::StartGenerate()
{
	GenerateCubes(CubeAmount);
}

void AArrayManagerC::GenerateCubes(int32 value)
{
	for (int32 i = 0; i < value; i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::FromInt(i));
		ATmpCubeC* NewCube = GetWorld()->SpawnActor<ATmpCubeC>(GeneratePosition(), GenerateRotation());
		TestArray.Add(NewCube);
	}
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ThisClass::DestroyCubes, TimeToDestroy, false);
}

// Called when the game starts or when spawned
void AArrayManagerC::BeginPlay()
{
	Super::BeginPlay();

	CubeAmount = rand() % 100 + 1;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::FromInt(CubeAmount));

	
	//GenerateCubes(CubeAmount);

	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::FromInt(TestArray.Num()));

	TimeToGenerate = 1.f;
	TimeToDestroy = 5.f;
	
	GetWorldTimerManager().SetTimer(GeneratorTimer, this, &ThisClass::StartGenerate, TimeToGenerate, false);
	
}

// Called every frame
void AArrayManagerC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArrayManagerC::DestroyCubes()
{
	for(ATmpCubeC* Array : TestArray)
	{
		Array->Destroy();
	}
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, TEXT("Array was Destroyed"));
}

