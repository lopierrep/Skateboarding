#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScoreWidgetInterface.generated.h"

UINTERFACE()
class UScoreWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class SKATEBOARDING_API IScoreWidgetInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetScore(const FString &TextToDisplay);
};
