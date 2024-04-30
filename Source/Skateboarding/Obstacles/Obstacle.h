// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class SKATEBOARDING_API AObstacle : public AActor
{
	GENERATED_BODY()

public:
	
	AObstacle();
	virtual void Tick(float DeltaTime) override;
	
protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UObstacleLogicComponent* ObstacleLogicComponent;
};
