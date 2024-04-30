#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"


UCLASS()
class SKATEBOARDING_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetScore(FString TextToDisplay);

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ScoreText;
	
};
