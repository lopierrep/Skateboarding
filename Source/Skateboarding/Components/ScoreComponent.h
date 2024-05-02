#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

class UCharacterMovementComponent;
class UScoreWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SKATEBOARDING_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScoreComponent();

protected:
	virtual void BeginPlay() override;

private:
    void TryToScore(const AActor* OtherActor);
	
	UFUNCTION()
	void OnJumped();

	UFUNCTION()
	virtual void OnCapsuleBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	
	UFUNCTION()
	virtual void OnCapsuleEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	UPROPERTY(EditAnywhere, Category=WidgetClass)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	
	UPROPERTY() UCharacterMovementComponent* CharacterMovementComponent;
	UPROPERTY() AActor* Obstacle;
	UPROPERTY()	UUserWidget* ScoreWidget;

	bool bJumped;
	bool bIsValidPoint;
	bool bOverObstacle;
	int32 Score;
	int32 JumpCounter;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
