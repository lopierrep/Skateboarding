// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObstacleLogicComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SKATEBOARDING_API UObstacleLogicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObstacleLogicComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int32 ScoreValue = 1;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetScoreValue() const
	{
		return ScoreValue;
	}
};
