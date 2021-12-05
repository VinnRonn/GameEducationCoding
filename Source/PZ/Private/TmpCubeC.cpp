// Fill out your copyright notice in the Description page of Project Settings.


#include "TmpCubeC.h"

#include "MovieSceneFwd.h"
#include "Components/BoxComponent.h"

// Sets default values
ATmpCubeC::ATmpCubeC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	CubeMesh->SetupAttachment(RootComponent);
	//BoxComponent->SetBoxExtent(FVector(80.f, 80.f, 80.f));
	//Mesh = CreateDefaultSubobject<UMeshComponent>("Mesh");

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/Geometry/Meshes/1M_Cube_Chamfer"));

	if (DefaultMesh.Succeeded())
	{
		CubeMesh->SetStaticMesh(DefaultMesh.Object);
		CubeMesh->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	}


}



// Called when the game starts or when spawned
void ATmpCubeC::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("I'm a cube!"));

	status = EStatus::Jumping;

	GetWorldTimerManager().SetTimer(StatusTimer,this, &ThisClass::ChangeStatus,
		1.f, true, -1);
}

// Called every frame
void ATmpCubeC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATmpCubeC::ChangeStatus()
{
	if (status == EStatus::Jumping)
	{
		status = EStatus::Running;
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Magenta, TEXT("Change Status"));
	} else
	{
		status = EStatus::Jumping;
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Purple, TEXT("Change Status"));
	}
	
}
