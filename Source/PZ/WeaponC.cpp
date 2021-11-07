// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponC.h"

#include "CollisionDebugDrawingPublic.h"
#include "Engine/Engine.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");

	SetRootComponent(SceneComponent);
	WeaponMesh->SetupAttachment(RootComponent);
}

FString InClip = "In Clip ";

void AWeapon::Fire()
{
	if (CanFire())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green,
			InClip + FString::FromInt(CurrentAmmoClip));
		WeaponTrace();
	}
	
	--CurrentAmmoClip;
	--CurrentAmmo;  //нужно подумать на эту тему
	
	if (CurrentAmmoClip == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
			InClip + FString::FromInt(CurrentAmmoClip));
		
	}
	if (EMouseButtons::Left)
	{
		FString Test21 = "Piu-Piu";
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Test21);	
	}
}

bool AWeapon::CanFire()
{
	if (CurrentAmmoClip > 0)
	{
		return true;
	}
	return false;
}
void AWeapon::Reaload_Implementation()
{
	if (CanReload())
	{
		CurrentAmmoClip += AmmoPerClip - CurrentAmmoClip;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
			InClip + FString::FromInt(CurrentAmmoClip));
	}
}

bool AWeapon::CanReload_Implementation()
{
	if (CurrentAmmo > 0 && CurrentAmmoClip < AmmoPerClip)
	{
		return true;
	}
	return false;
}
void AWeapon::WeaponTrace()
{
	
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector TraceEnd =  TraceStart + (SocketTransform.GetRotation().GetForwardVector() * Range);
	
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green,
		false, 1.0f, 0, 0.5f);
	
	FHitResult OutHit;
	GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECollisionChannel::ECC_WorldStatic);

	if (OutHit.bBlockingHit)
	{
		DrawDebugBox(GetWorld(), OutHit.ImpactPoint,
			FVector(10, 10, 10), FColor::Magenta, false, 2.0f);
	}
}



// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

