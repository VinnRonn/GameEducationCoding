#include "BasePawn.h"

#include "Camera/CameraComponent.h"
#include "Engine/CollisionProfile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

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
	
//	SceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	SetRootComponent(SphereComp);   //to think about Root movement
	
	MovementComp = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComp");
	MovementComp->SetUpdatedComponent(SphereComp);
	

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
}

UPawnMovementComponent* ABasePawn::GetMovementComponent() const
{
	return MovementComp;
}

void ABasePawn::MoveForward(float AxisValue)
{
	if(AxisValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void ABasePawn::MoveRight(float AxisValue)
{
	if(AxisValue != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
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

