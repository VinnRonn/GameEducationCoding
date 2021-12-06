#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "SpyCameraC.generated.h"

class UBoxComponent;

DECLARE_EVENT(ASpyCameraC, FOnChangeMaterial);
DECLARE_EVENT(ASpyCameraC, FOnRevertMaterial);
/*DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangeMaterial);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevertMaterial);*/


UCLASS()
class PZ_API ASpyCameraC : public ACameraActor
{
	GENERATED_BODY()

public:
	
	ASpyCameraC();

	bool bCameraCatch;
	FTimerHandle StartCatchTimer;
	FTimerHandle EndCatchTimer;

	UPROPERTY(BlueprintReadWrite)
	float StartCatchRate;
	float EndCatchRate;

	virtual void BeginPlay() override;

	// Timers
	void StartCheckOverlap();
	void EndCheckOverlap();

	//UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnChangeMaterial OnChangeMaterial;
	//UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnRevertMaterial OnRevertMaterial;
	
	UFUNCTION()
	void ChangeMaterial();

	UFUNCTION()
	void RevertMaterial();

	
protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
