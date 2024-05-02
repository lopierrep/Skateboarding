#include "ScoreComponent.h"

#include "SkateMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Skateboarding/HUD/ScoreWidget.h"
#include "Skateboarding/Obstacles/ObstacleLogicComponent.h"


UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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
}

void UScoreComponent::OnJumped()
{
	PrimaryComponentTick.bCanEverTick = true;
	bJumped = true;
	if (bOverObstacle) JumpCounter ++;
}

void UScoreComponent::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->FindComponentByClass<UObstacleLogicComponent>()) return;
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
		bOverObstacle = false;		
	}
	else
	{
		if (!CharacterMovementComponent->IsFalling()) return;	 	
	}
	if (bIsValidPoint && bJumped && JumpCounter == 0 && CharacterMovementComponent->IsFalling())
	{
		Score = Score + OtherActor->FindComponentByClass<UObstacleLogicComponent>()->GetScoreValue();
		JumpCounter = 0;
		IScoreWidgetInterface::Execute_SetScore(ScoreWidget, FString::FromInt(Score));
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
		PrimaryComponentTick.bCanEverTick = false;
	}	
}