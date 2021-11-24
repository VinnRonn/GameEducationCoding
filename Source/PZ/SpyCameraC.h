#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "SpyCameraC.generated.h"

class UBoxComponent;

UCLASS()
class PZ_API ASpyCameraC : public ACameraActor
{
	GENERATED_BODY()

public:
	
	ASpyCameraC();
	
protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;
};
