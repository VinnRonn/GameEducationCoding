// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyCameraC.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"


ASpyCameraC::ASpyCameraC()
{
	bCameraCatch = false;
	StartCatchRate = 5.0f;
	EndCatchRate = 10.0f;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComp->SetBoxExtent(FVector (500.0f));
	BoxComp->SetCollisionObjectType(ECC_WorldStatic);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore); //не помню, посмотреть еще раз
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetupAttachment(GetRootComponent());
	
}

void ASpyCameraC::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASpyCameraC::BoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ASpyCameraC::BoxEndOverlap);

	OnChangeMaterial.AddUFunction(this, "ChangeMaterial");
	OnRevertMaterial.AddUFunction(this, "RevertMaterial");

	/*OnChangeMaterial.AddDynamic(this, &ASpyCameraC::ChangeMaterial);
	OnRevertMaterial.AddDynamic(this, &ASpyCameraC::RevertMaterial);*/
	
	
}


void ASpyCameraC::StartCheckOverlap()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("OnOverlap's now!!!"));
	bCameraCatch = true;

	OnChangeMaterial.Broadcast();
	
}

void ASpyCameraC::EndCheckOverlap() //удалить мб?
{
	OnRevertMaterial.Broadcast();
}

void ASpyCameraC::ChangeMaterial()
{
}

void ASpyCameraC::RevertMaterial()
{
}


void ASpyCameraC::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().SetTimer(StartCatchTimer, this, &ASpyCameraC::StartCheckOverlap,
	StartCatchRate, false, -1);
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	
	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.0f;
	TransitionParams.bLockOutgoing = true; //почитать
	PC->SetViewTarget(this, TransitionParams);
	
}


void ASpyCameraC::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//reset StartCatchTimer
	GetWorldTimerManager().ClearTimer(StartCatchTimer);
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.0f;
	TransitionParams.bLockOutgoing = true;
	PC->SetViewTarget(PC->GetPawn(), TransitionParams);

	if (bCameraCatch)
	{
		GetWorldTimerManager().SetTimer(EndCatchTimer, this, &ASpyCameraC::EndCheckOverlap,
			EndCatchRate, false, -1);
		
	}

	bCameraCatch = false;
}
