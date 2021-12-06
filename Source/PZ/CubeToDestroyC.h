// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeToDestroyC.generated.h"

UCLASS()
class PZ_API ACubeToDestroyC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeToDestroyC();

	UPROPERTY();
	int32 Health;
	
	UFUNCTION(BlueprintCallable)
	void DestroyActor();

	UFUNCTION(BlueprintCallable)
	void ApplyDamage();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
