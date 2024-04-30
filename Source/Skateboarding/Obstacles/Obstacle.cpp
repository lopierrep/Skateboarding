#include "Obstacle.h"

#include "ObstacleLogicComponent.h"
#include "Components/BoxComponent.h"


AObstacle::AObstacle()
{	
	PrimaryActorTick.bCanEverTick = false;
	
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObstacleMesh");
	ObstacleMesh->SetupAttachment(RootComponent);
	ObstacleMesh->SetCollisionResponseToAllChannels(ECR_Block);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxSphere");
	BoxCollider->SetupAttachment(ObstacleMesh);
	BoxCollider->SetBoxExtent(FVector(50.0f, 50.0f, 200.f), true);
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	\

	ObstacleLogicComponent = CreateDefaultSubobject<UObstacleLogicComponent>("ObstacleLogicComponent");
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

