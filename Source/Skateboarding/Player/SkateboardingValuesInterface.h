#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkateboardingValuesInterface.generated.h"

UINTERFACE()
class USkateboardingValuesInterface : public UInterface
{
	GENERATED_BODY()
};

class SKATEBOARDING_API ISkateboardingValuesInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetPlayerInputs(float &MoveForward, float &MoveRight);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetSpeedUp();	
};
