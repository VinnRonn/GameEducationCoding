#include "CubeCollisionC.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

ACubeCollisionC::ACubeCollisionC()
{
	PrimaryActorTick.bCanEverTick = true;


	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
	CubeMesh->SetupAttachment(RootComponent);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	CollisionBox->SetBoxExtent(FVector(80.f, 80.f, 80.f));
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	
}

void ACubeCollisionC::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("On Trigger Overlap"));
	if(OnColorChange.IsBound())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IsBound"));
		OnColorChange.Broadcast();	
	}
}

void ACubeCollisionC::MoveMesh()
{
	FVector MeshLocation = GetActorLocation();
	MeshLocation.X += 100.f;
	SetActorLocation(MeshLocation);
}

void ACubeCollisionC::BeginPlay()
{
	Super::BeginPlay();

	OnMoveMesh.BindDynamic(this, &ThisClass::MoveMesh);
	OnColorChange.Add(OnMoveMesh);
	
}

// Called every frame
void ACubeCollisionC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

