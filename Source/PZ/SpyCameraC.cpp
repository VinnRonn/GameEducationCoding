// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyCameraC.h"
#include "Components/BoxComponent.h"


ASpyCameraC::ASpyCameraC()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComp->SetBoxExtent(FVector (500.0f));
	BoxComp->SetCollisionObjectType(ECC_WorldStatic);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore); //не помню, посмотреть еще раз
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetupAttachment(GetRootComponent());
}
