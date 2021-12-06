// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TmpCubeC.generated.h"

UENUM(BlueprintType)
enum class EStatus : uint8
{
	Jumping = 0 UMETA(DisplayName = "Jumping"),
	Running = 1 UMETA(DisplayName = "Running"),
	MAX
};

UCLASS()
class PZ_API ATmpCubeC : public AActor
{
	GENERATED_BODY()

	

	
public:	
	// Sets default values for this actor's properties
	ATmpCubeC();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComponent;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* CubeMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EStatus> status;

	UFUNCTION()
	void ChangeStatus();

	FTimerHandle StatusTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
