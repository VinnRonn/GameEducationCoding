#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class PZ_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SceneComp;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComp;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY()
	UMaterialInterface* PawnMaterial;
	UPROPERTY()
	UMaterialInterface* Material;
	UPROPERTY()
	UMaterialInstanceDynamic* NewPawnMaterial;
	


	//UMaterialInterface* NewPawnMaterial;
	
	UPROPERTY(VisibleAnywhere)
	UPawnMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	virtual UPawnMovementComponent* GetMovementComponent() const override; //посмотреть подробнее

	UPROPERTY(Transient)
	AActor* ViewActor;

	/*UPROPERTY()
	int32 MaterialIndex;*/
	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	void CameraBlendComplete();

	UFUNCTION(BlueprintCallable)
	void ChangeMaterial();

	UFUNCTION(BlueprintCallable)
	void RevertMaterial();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
