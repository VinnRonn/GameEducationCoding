 #include "CubeC.h"
#include "TimerManager.h"


ACubeC::ACubeC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DestroyDuration = 10.0f;


}

// Called when the game starts or when spawned
void ACubeC::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &ACubeC::Destroyed,
	 4.0f, false, -1);
	
}

void ACubeC::Destroyed()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,
		TEXT("Cube was Destroied!"));
	Destroy();
}


// Called every frame
void ACubeC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

