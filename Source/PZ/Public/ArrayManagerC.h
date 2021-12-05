// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TmpCubeC.h"
#include "ArrayManagerC.generated.h"

UCLASS()
class PZ_API AArrayManagerC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrayManagerC();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CubeAmount;

	UFUNCTION()
	static FVector GeneratePosition();
	UFUNCTION()
	static FRotator GenerateRotation();
	
	UFUNCTION()
	void StartGenerate();
	UFUNCTION()
	void GenerateCubes(int32 value);

	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObjectsInContainer
	TArray<ATmpCubeC*> TestArray;

	UFUNCTION()
	void DestroyCubes();

	int32 TimeToGenerate;
	int32 TimeToDestroy;

	FTimerHandle GeneratorTimer;
	FTimerHandle DestroyTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
