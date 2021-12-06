// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DamageAreaC.generated.h"

DECLARE_EVENT(ADamageArea, FOnDamage);

class USceneComponent;
class UBoxComponent;



UCLASS()
class PZ_API ADamageAreaC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageAreaC();

	UPROPERTY(BlueprintReadWrite)
	class USceneComponent* SceneComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* BoxCollision;

	//UPROPERTY()
	FOnDamage OnDamage;
	
	FTimerHandle DamageTimer;

	
	UFUNCTION(BlueprintCallable)
	void Damage();

	void StartCheckOverlap();

	bool bOverlap;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
