// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroChar.h"
#include "TimerManager.h"



AHeroChar::AHeroChar()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHeroChar::BeginPlay()
{
	Super::BeginPlay();

	Health = 80;
	HealthUp = 3;
	RecoveryHealthDuration = 2.0f;
	DamageRate = 1.0f;
	GetWorldTimerManager().SetTimer(HealthRecoveryHandle, this, &AHeroChar::RecoveryHeath,
		RecoveryHealthDuration, true, -1);
	GetWorldTimerManager().SetTimer(DamageHandle, this, &AHeroChar::GetDamage,
		DamageRate, true, -1);

	OnDestroyActor.AddUFunction(this, "DestroyActor");
	OnApplyDamage.AddUFunction(this, "ApplyDamage");
	
}

void AHeroChar::RecoveryHeath()
{
	if (Health < 100)
	{
		if ((Health + HealthUp) > 100)
		{
			Health = 100;
		} else
		{
			Health = Health + 3;
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f,
			FColor::Green, TEXT("Curren Health: ") + FString::FromInt(Health));
	}
}

void AHeroChar::GetDamage()
{
	if (Health > 0)
	{
		OnApplyDamage.Broadcast();
	} else
	{
		OnDestroyActor.Broadcast();
	}
}

void AHeroChar::DestroyActor()
{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f,
	FColor::Yellow, TEXT("HeroChar Destroyed!!!"));
		Destroy();

}

void AHeroChar::ApplyDamage()
{
	Health -= 10.0f;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,
		TEXT("Take Damage!!!") + FString::FromInt(Health));
}


void AHeroChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

