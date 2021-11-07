// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "ReloadableInterfaceC.h"
#include "GameFramework/Actor.h"
#include "WeaponC.generated.h"


UCLASS()
class PZ_API AWeapon : public AActor, public IReloadableInterface
{

	

	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeapon();
	
	UPROPERTY(BlueprintReadWrite)
	int32 MaxAmmo = 12;
	
	UPROPERTY(BlueprintReadWrite)
	int32 AmmoPerClip = 4;

	UPROPERTY(BlueprintReadWrite)
	int32 Damage = 6;

	UPROPERTY(BlueprintReadWrite)
	float ReloadDuration = 2.0;

	UPROPERTY(BlueprintReadWrite)
	int32 Range = 1000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo = 12;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmoClip = 4;

	UPROPERTY(BlueprintReadWrite)
	bool bIsReloading;
	

	UFUNCTION(BlueprintCallable)
	void Fire();
	
	UFUNCTION(BlueprintCallable)
	bool CanFire();
	
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;
	
	UFUNCTION(BlueprintCallable,Category="Utilities|Transformation", meta=(Keywords="Bone") )
	void WeaponTrace();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reaload();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanReload();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
