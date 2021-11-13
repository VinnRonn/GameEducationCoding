// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "Interfaces/ReloadableInterfaceC.h"
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
	int32 MaxAmmo;
	
	UPROPERTY(BlueprintReadWrite)
	int32 AmmoPerClip;

	UPROPERTY(BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(BlueprintReadWrite)
	float ReloadDuration;

	UPROPERTY(BlueprintReadWrite)
	int32 Range;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName MuzzleSocketName;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmoClip;

	UPROPERTY(BlueprintReadWrite)
	bool bIsReloading;
	

	UFUNCTION(BlueprintCallable)
	void Fire();
	
	UFUNCTION(BlueprintCallable)
	bool CanFire();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanReload();

	UFUNCTION(BlueprintCallable)
	void Reloading();
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UFUNCTION()
	void UseAmmo();


	UFUNCTION(BlueprintCallable,Category="Utilities|Transformation", meta=(Keywords="Bone") )
	void WeaponTrace();

	FTimerHandle ReloadingTimer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
