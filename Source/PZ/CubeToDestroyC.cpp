#include "CubeToDestroyC.h"

#include "HeroChar.h"
#include "Kismet/GameplayStatics.h"

ACubeToDestroyC::ACubeToDestroyC()
{
	PrimaryActorTick.bCanEverTick = true;

}



void ACubeToDestroyC::BeginPlay()
{
	Super::BeginPlay();
	Health = 100;
	TArray<AActor*> HeroCharActors;
	UGameplayStatics::GetAllActorsOfClass(this, AHeroChar::StaticClass(), HeroCharActors);
	for (AActor* HeroChar : HeroCharActors)
	{
		AHeroChar* hero = Cast<AHeroChar>(HeroChar);
		if (hero)
		{
			hero->OnDestroyActor.AddUFunction(this, "DestroyActor");
			hero->OnDestroyActor.AddUFunction(this, "ApplyDamage");
		}
	}
}

void ACubeToDestroyC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubeToDestroyC::DestroyActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f,
		FColor::Cyan, TEXT("CubeToDestroy was destroyed!!!"));
	Destroy();
}

void ACubeToDestroyC::ApplyDamage()
{
	Health -= 10;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f,
		FColor::Cyan, TEXT("CubeToDestroy get damage: ") + FString::FromInt(Health));
}
