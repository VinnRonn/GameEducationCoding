// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CubeCollisionC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnColorChange);
DECLARE_DYNAMIC_DELEGATE(FOnMoveMesh);

UCLASS()
class PZ_API ACubeCollisionC : public AActor
{
	GENERATED_BODY()
	
public:
	ACubeCollisionC();

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBox;

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void MoveMesh();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnColorChange OnColorChange;
	UPROPERTY()
	FOnMoveMesh OnMoveMesh;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
