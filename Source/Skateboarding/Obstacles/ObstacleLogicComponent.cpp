
#include "ObstacleLogicComponent.h"


UObstacleLogicComponent::UObstacleLogicComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void UObstacleLogicComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UObstacleLogicComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

