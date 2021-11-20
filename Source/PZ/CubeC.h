// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeC.generated.h"




UCLASS()
class PZ_API ACubeC : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACubeC();
	FTimerHandle DestroyHandle;

	float DestroyDuration;
	
	virtual void Destroyed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};