// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponC.h"

#include "CollisionDebugDrawingPublic.h"
#include "Engine/Engine.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");

	SetRootComponent(SceneComponent);
	WeaponMesh->SetupAttachment(RootComponent);

	MaxAmmo = 12;
	AmmoPerClip = 4;
	Damage = 6;
	ReloadDuration = 2.0;
	Range = 1000;
	MuzzleSocketName = "MuzzleSocket";
	CurrentAmmo = 12;
	CurrentAmmoClip = 4;
	bIsReloading = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

bool AWeapon::CanFire() const
{
	if (CurrentAmmoClip > 0)
	{
		return true;
	}
	return false;
}


FString InClip = "In Clip ";
FString CurrAmmo = "CurAmmo ";

void AWeapon::UseAmmo()
{
	--CurrentAmmoClip;
}

void AWeapon::Fire()
{
	if (CanFire())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White,
			CurrAmmo + FString::FromInt(CurrentAmmo));
		WeaponTrace();
		
		UseAmmo();
		--CurrentAmmo;
		if(CurrentAmmoClip == 0)
		{
			Reload_Implementation();
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
			InClip + FString::FromInt(CurrentAmmoClip));

}


//FTimerHandle ReloadingTimer;
//~ Start Reloading Interface
bool AWeapon::CanReload_Implementation() const
{
	if (CurrentAmmo > 0 && CurrentAmmoClip < AmmoPerClip)
	{
		return true;
	}
	return false;
}

void AWeapon::Reload_Implementation()
{
	if (CanReload())
	{
		bIsReloading = true;
		GetWorldTimerManager().SetTimer(ReloadingTimer, this,
			&AWeapon::Reloading,  1.0f, false, -1);
	}
}

//~ End Reloading Interface
void AWeapon::Reloading()
{
	GEngine->AddOnScreenDebugMessage(-1, ReloadDuration, FColor::Emerald,
			TEXT("Reloading!!!"));
	if (CurrentAmmo >= AmmoPerClip)
	{
		CurrentAmmoClip += AmmoPerClip - CurrentAmmoClip;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
			InClip + FString::FromInt(CurrentAmmoClip));
	} else
	{
		CurrentAmmoClip += CurrentAmmo;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
InClip + FString::FromInt(CurrentAmmoClip));
	}
	bIsReloading = false;
}

void AWeapon::WeaponTrace()
{
	
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector TraceEnd = TraceStart + (SocketTransform.GetRotation().GetForwardVector() * Range);
	
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



// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

