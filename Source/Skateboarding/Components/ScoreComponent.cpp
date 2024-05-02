#include "ScoreComponent.h"

#include "SkateMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Skateboarding/HUD/ScoreWidget.h"
#include "Skateboarding/Obstacles/Obstacle.h"
#include "Skateboarding/Obstacles/ObstacleLogicComponent.h"


UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterMovementComponent = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();

	ScoreWidget = CreateWidget(GetWorld(), ScoreWidgetClass);
	ScoreWidget->AddToViewport();
	IScoreWidgetInterface::Execute_SetScore(ScoreWidget, FString::FromInt(Score));
	
	GetOwner()->FindComponentByClass<UCapsuleComponent>()->OnComponentBeginOverlap.AddDynamic(this, &UScoreComponent::OnCapsuleBeginOverlap);
	GetOwner()->FindComponentByClass<UCapsuleComponent>()->OnComponentEndOverlap.AddDynamic(this, &UScoreComponent::OnCapsuleEndOverlap);
	GetOwner()->FindComponentByClass<USkateMovementComponent>()->OnJumped.AddDynamic(this, &UScoreComponent::OnJumped);
	
	SetComponentTickEnabled(false);
}



void UScoreComponent::OnJumped()
{	
	bJumped = true;
	SetComponentTickEnabled(true);
	if (bOverObstacle) JumpCounter ++;
}

void UScoreComponent::TryToScore(const AActor* OtherActor)
{
	const float ColliderHeight = OtherActor->FindComponentByClass<UBoxComponent>()->GetComponentLocation().Z;
	const float PlayerHeight = GetOwner()->GetActorLocation().Z;
 	if (bIsValidPoint && bJumped && JumpCounter == 0 && CharacterMovementComponent->IsFalling() && ColliderHeight >= PlayerHeight)
	{
		Score = Score + OtherActor->FindComponentByClass<UObstacleLogicComponent>()->GetScoreValue();
		IScoreWidgetInterface::Execute_SetScore(ScoreWidget, FString::FromInt(Score));
		JumpCounter = 0;		
	}
}

void UScoreComponent::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->FindComponentByClass<UObstacleLogicComponent>()) return;
	if (Obstacle != nullptr)
	{
		TryToScore(Obstacle);
	}
	Obstacle = OtherActor;
	bOverObstacle = true;
	JumpCounter = 0;
	bIsValidPoint = true;
}

void UScoreComponent::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
 	if (!OtherActor->FindComponentByClass<UObstacleLogicComponent>() || CharacterMovementComponent == nullptr) return;
	if (Obstacle == OtherActor)
	{
		TryToScore(OtherActor);
		Obstacle = nullptr;
		bOverObstacle = false;
	}
}

void UScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bJumped || CharacterMovementComponent == nullptr) return;
	if (CharacterMovementComponent->IsFalling())
	{
		if (bOverObstacle && bIsValidPoint)
		{
			bIsValidPoint = CharacterMovementComponent->IsFalling();
		}
	}
	else
	{
		bJumped = false;
		bIsValidPoint = false;
		SetComponentTickEnabled(false);
	}	
}