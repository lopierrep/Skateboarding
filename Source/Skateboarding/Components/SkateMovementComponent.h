
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skateboarding/Player/SkateboardingValuesInterface.h"
#include "SkateMovementComponent.generated.h"

class UCharacterMovementComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumped);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class SKATEBOARDING_API USkateMovementComponent : public UActorComponent, public ISkateboardingValuesInterface
{

	GENERATED_BODY()
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
						   FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void GetPlayerInputs_Implementation(float& MoveForward, float& MoveRight) override;
	virtual bool GetSpeedUp_Implementation() override;

	USkateMovementComponent();

	void SetupInputs(class UInputComponent* PlayerInputComponent);

	UPROPERTY()
	FOnJumped OnJumped;

protected:	
	virtual void BeginPlay() override;
	
	void Look(const FInputActionValue& Value);
	void MoveForward(const FInputActionValue& Value);
	void StopMoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void SpeedUp(const FInputActionValue& Value);	
	void Jump();
	void StopJumping();	

private:
	//Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpeedUpAction;

	UPROPERTY()	AController* Controller;
	UPROPERTY()	APawn* Pawn;
	UPROPERTY() UCharacterMovementComponent* CharacterMovementComponent;
	
	//Speeds values
	UPROPERTY(EditAnywhere, Category=Speed)	float ForwardSpeed = 700.f;
	UPROPERTY(EditAnywhere, Category=Speed)	float BackwardSpeed = 100.f;
	UPROPERTY(EditAnywhere, Category=Speed)	float SpeedUpSpeed = 1200.f;
	UPROPERTY(EditAnywhere, Category=Speed)	float MinimumSpeedToJump = 150.f;
	UPROPERTY(EditAnywhere, Category=Speed)	float RotationSpeedInMovement = 2.5f;
	UPROPERTY(EditAnywhere, Category=Speed)	float RotationSpeedIdle = 0.5f;

	float CurrentForwardValue;
	float ForwardInputValue;
	float RightInputValue;
	bool bMovingForward = true;
	bool bWasMovingForward;
	bool bSpeedingUp;

	//Jump
	float DelayBetweenJumps = 0.15f;
	bool bCanJump = true;
	FTimerHandle MemberTimerHandle;

	void ManageDelayBetweenJump();
	void SetCanJump();
	void SlideAfterMovement();
};

