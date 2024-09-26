#include "BasePawn.h"

#include "SpyCameraC.h"
#include "Camera/CameraComponent.h"
#include "Engine/CollisionProfile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/GameplayStatics.h"
//#include "MaterialInstance"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComp->SetSphereRadius(50.0f);
	SphereComp->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	

	//SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArmComp->TargetArmLength = 400.0f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.0f;
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f));

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComp->SetupAttachment(SphereComp);
	CameraComp->SetupAttachment(SpringArmComp);
	

	/*SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComp");
	SkeletalMeshComp->SetupAttachment(SphereComp);*/
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(SphereComp);
	
//	SceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	SetRootComponent(SphereComp);   //to think about Root movement
	
	MovementComp = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComp");
	MovementComp->SetUpdatedComponent(SphereComp);
	

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	PawnMaterial = StaticMeshComp->GetMaterial(0);
	
}

UPawnMovementComponent* ABasePawn::GetMovementComponent() const
{
	return MovementComp;
}

void ABasePawn::MoveForward(float AxisValue)
{
	if(AxisValue != 0.0f)
	{
		AddMovementInput(ViewActor-> GetActorForwardVector(), AxisValue);
	}
}

void ABasePawn::MoveRight(float AxisValue)
{
	if(AxisValue != 0.0f)
	{
		AddMovementInput(ViewActor->GetActorRightVector(), AxisValue);
	}
}

void ABasePawn::CameraBlendComplete()
{
	ViewActor = GetController()->GetViewTarget();
}

void ABasePawn::ChangeMaterial()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Color changes"));
	
	//UMaterialInstance Color = SkeletalMeshComp->GetMaterial(0);
	//SkeletalMeshComp->SetMaterial(0, NewPawnMaterial);
	
	//StaticMeshComp->SetMaterial(0, NewPawnMaterial);
	StaticMeshComp->SetVectorParameterValueOnMaterials("BaseColor", FVector(0.f, 1.0f, 0.f));
	//StaticMeshComp->SetMaterial(0, PawnMaterial);
	
}

void ABasePawn::RevertMaterial()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Color revers"));
	//SkeletalMeshComp->SetMaterial(0, PawnMaterial);
	StaticMeshComp->SetMaterial(0, PawnMaterial);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	//PawnMaterial = SkeletalMeshComp->GetMaterial(0);
	NewPawnMaterial = UMaterialInstanceDynamic::Create(Material, this);
	NewPawnMaterial->SetVectorParameterValue("Color", FLinearColor::Green);
	
	//SkeletalMeshComp->SetMaterial(0, PawnMaterial);
	
	APlayerCameraManager* CM = UGameplayStatics::GetPlayerCameraManager(this, 0); //внимательно изучить
	CM->OnBlendComplete().AddUObject(this, &ABasePawn::CameraBlendComplete);
	ViewActor = CM->GetViewTarget();

	TArray<AActor*> spyCameras;  //не оптимально ни разу
	UGameplayStatics::GetAllActorsOfClass(this, ASpyCameraC::StaticClass(), spyCameras);
	for(AActor* spyCamera : spyCameras)
	{
		ASpyCameraC* camera = Cast<ASpyCameraC>(spyCamera);
		if (camera)
		{
			camera->OnChangeMaterial.AddUFunction(this, "ChangeMaterial");
			camera->OnRevertMaterial.AddUFunction(this, "RevertMaterial");
			/*camera->OnChangeMaterial.AddDynamic(this, &ABasePawn::ChangeMaterial);
			camera->OnRevertMaterial.AddDynamic(this, &ABasePawn::RevertMaterial);*/
		}
	}
}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePawn::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ABasePawn::AddControllerYawInput);

}

