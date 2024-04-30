// Fill out your copyright notice in the Description page of Project Settings.

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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GetPlayerInputs(float &MoveForward, float &MoveRight);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GetSpeedUp(bool &SpeedUp);

	
};
