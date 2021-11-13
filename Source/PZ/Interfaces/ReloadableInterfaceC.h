#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReloadableInterfaceC.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UReloadableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IReloadableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanReload();
};