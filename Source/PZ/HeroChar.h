#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeroChar.generated.h"

DECLARE_EVENT(AHeroChar, FOnDestroyActor);
DECLARE_EVENT(AHeroChar, FOnApplyDamage);
//DECLARE_DELEGATE( FOnApplyDamage);

UCLASS()
class PZ_API AHeroChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroChar();

	UPROPERTY(BlueprintReadWrite)
	int32 Health;

	UPROPERTY(BlueprintReadWrite)
	int32 HealthUp;

	UPROPERTY(BlueprintReadWrite)
	int32 Stamina;
	
	FTimerHandle HealthRecoveryHandle;

	UPROPERTY(BlueprintReadWrite)
	float RecoveryHealthDuration;

	void RecoveryHeath();

	FTimerHandle DamageHandle;
	
	UPROPERTY(BlueprintReadWrite)
	float DamageRate;

	UFUNCTION(BlueprintCallable)
	void GetDamage();
	
	FOnDestroyActor OnDestroyActor;

	FOnApplyDamage OnApplyDamage;


	
	UFUNCTION(BlueprintCallable)
	void DestroyActor();

	UFUNCTION(BlueprintCallable)
	void ApplyDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
