// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroChar.h"
#include "TimerManager.h"

// Sets default values
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
	if (Health > 90)
	{
		//GetWorldTimerManager().UnPauseTimer(DamageHandle);
		Health -= 10.0f;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,
			TEXT("Take Damage!!!") + FString::FromInt(Health));
	} 
}


void AHeroChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

