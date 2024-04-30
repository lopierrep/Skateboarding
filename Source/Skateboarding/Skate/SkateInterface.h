#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkateInterface.generated.h"

UINTERFACE()
class USkateInterface : public UInterface
{
	GENERATED_BODY()
};

class SKATEBOARDING_API ISkateInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Jump();
};
