#include "SkateMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Skateboarding/Player/SkateCharacter.h"
#include "Skateboarding/Skate/SkateInterface.h"


void USkateMovementComponent::GetPlayerInputs_Implementation(float& MoveForward, float& MoveRight)
{
	MoveForward = ForwardInputValue;
	MoveRight = RightInputValue;
}

bool USkateMovementComponent::GetSpeedUp_Implementation()
{
	return bSpeedingUp;	
}

USkateMovementComponent::USkateMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true	;
}

void USkateMovementComponent::SetupInputs(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &USkateMovementComponent::Look);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &USkateMovementComponent::MoveForward);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Completed, this, &USkateMovementComponent::StopMoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &USkateMovementComponent::MoveRight);	
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &USkateMovementComponent::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &USkateMovementComponent::StopJumping);	
		EnhancedInputComponent->BindAction(SpeedUpAction, ETriggerEvent::Triggered, this, &USkateMovementComponent::SpeedUp);
	}
}


void USkateMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Pawn = Cast<APawn>(GetOwner());
	if (Pawn != nullptr)
	{
		Controller = Pawn->GetController();		
	}
	CharacterMovementComponent = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
	if (CharacterMovementComponent) CharacterMovementComponent->MaxWalkSpeed = ForwardSpeed;

}


void USkateMovementComponent::MoveForward(const FInputActionValue& Value)
{
	if (CharacterMovementComponent == nullptr || Pawn == nullptr) return;
	
	ForwardInputValue = Value.Get<float>();
	float InterpolationSpeed;
	if (ForwardInputValue * CurrentForwardValue < 0)
	{
		InterpolationSpeed = CharacterMovementComponent->Velocity.Length() >= ForwardSpeed? 0.25f : 0.5f;
	}
	else
	{
		InterpolationSpeed = 2.f;
	}

	CurrentForwardValue = FMath::FInterpTo(CurrentForwardValue, ForwardInputValue, Controller->GetWorld()->GetDeltaSeconds(), InterpolationSpeed);
	bWasMovingForward = false;

	if (CurrentForwardValue >= 0)
	{
		if (!bMovingForward)
		{
			bMovingForward = true;
			CharacterMovementComponent->MaxWalkSpeed = ForwardSpeed;
		}		
	}
	else
	{
		if (bMovingForward)
		{
			bMovingForward = false;
			CharacterMovementComponent->MaxWalkSpeed = BackwardSpeed;
		}
	}
	Pawn->AddMovementInput(Pawn->GetActorForwardVector(), CurrentForwardValue);	
}


void USkateMovementComponent::StopMoveForward(const FInputActionValue& Value)
{
	if (CharacterMovementComponent == nullptr) return;
	
	ForwardInputValue = Value.Get<float>();
	bWasMovingForward = CurrentForwardValue >= 0;
	if (CurrentForwardValue < 0) CurrentForwardValue = 0;
}


void USkateMovementComponent::MoveRight(const FInputActionValue& Value)
{
	if (CharacterMovementComponent == nullptr) return;
	RightInputValue = Value.Get<float>();
	float YawDeltaRotation = 0.f;
	YawDeltaRotation = CharacterMovementComponent->Velocity.Length() == 0.f ? RotationSpeedInMovement : RotationSpeedIdle;
	YawDeltaRotation = YawDeltaRotation * RightInputValue; 
	GetOwner()->AddActorLocalRotation(FRotator(0, YawDeltaRotation, 0));
}


void USkateMovementComponent::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr && Pawn!= nullptr)
	{		
		Pawn->AddControllerYawInput(LookAxisVector.X);
		Pawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}


void USkateMovementComponent::Jump()
{
	if (!bCanJump || CharacterMovementComponent == nullptr) return;

	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (PlayerCharacter == nullptr) return;
	
	if (CharacterMovementComponent->Velocity.Length() >= MinimumSpeedToJump && !CharacterMovementComponent->IsFalling())
	{
		bCanJump = false;
		PlayerCharacter->Jump();
		OnJumped.Broadcast();
		ISkateInterface::Execute_Jump(GetOwner()->FindComponentByClass<UChildActorComponent>()->GetChildActor());
	}

}


void USkateMovementComponent::StopJumping()
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (PlayerCharacter == nullptr) return;

	PlayerCharacter->StopJumping();	
}


void USkateMovementComponent::SpeedUp(const FInputActionValue& Value)
{
	if (CharacterMovementComponent == nullptr || CurrentForwardValue < 0) return;
	bSpeedingUp = Value.Get<bool>();
	CharacterMovementComponent->MaxWalkSpeed = bSpeedingUp ? SpeedUpSpeed : ForwardSpeed;
}


void USkateMovementComponent::ManageDelayBetweenJump()
{
	if (CharacterMovementComponent == nullptr) return;
	if (!bCanJump && !CharacterMovementComponent->IsFalling())
	{
		if (GetOwner()->GetWorldTimerManager().IsTimerActive(MemberTimerHandle)) return;	
		GetOwner()->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &USkateMovementComponent::SetCanJump, DelayBetweenJumps);
	}	
}


void USkateMovementComponent::SetCanJump()
{
	bCanJump = true;	
	GetOwner()->GetWorldTimerManager().ClearTimer(MemberTimerHandle);
}


void USkateMovementComponent::SlideAfterMovement()
{
	if (Pawn == nullptr || !bWasMovingForward) return;
	
	CurrentForwardValue = FMath::FInterpTo(CurrentForwardValue, 0.f, Controller->GetWorld()->GetDeltaSeconds(), 0.5f);
	Pawn->AddMovementInput(Pawn->GetActorForwardVector(), CurrentForwardValue);
	if (CurrentForwardValue < 0.025)
	{
		bWasMovingForward = false;
		CurrentForwardValue = 0;
	}
}


void USkateMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ManageDelayBetweenJump();
	SlideAfterMovement();
}

