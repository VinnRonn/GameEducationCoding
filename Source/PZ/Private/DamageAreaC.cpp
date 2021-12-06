// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageAreaC.h"

#include "DiffUtils.h"

// Sets default values
ADamageAreaC::ADamageAreaC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");

	SetRootComponent(SceneComp);
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetBoxExtent(FVector(300.f));
	BoxCollision->SetCollisionObjectType(ECC_WorldStatic);
	
	bOverlap = false;
}

void ADamageAreaC::Damage()
{
}

void ADamageAreaC::StartCheckOverlap()
{
	OnDamage.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Damage"));
	
	bOverlap = true;
}

// Called when the game starts or when spawned
void ADamageAreaC::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADamageAreaC::BoxBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ADamageAreaC::BoxEndOverlap);

	OnDamage.AddUFunction(this, "Damage");
}

void ADamageAreaC::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Start overlap"));
	GetWorldTimerManager().SetTimer(DamageTimer, this, &ADamageAreaC::StartCheckOverlap,
		1.f, true, -1);

}

void ADamageAreaC::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("End overlap"));
	
	if (bOverlap)
	{
		GetWorldTimerManager().PauseTimer(DamageTimer);
	}
	bOverlap = false;
}

// Called every frame
void ADamageAreaC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

