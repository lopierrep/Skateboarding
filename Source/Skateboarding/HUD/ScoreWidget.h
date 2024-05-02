#pragma once

#include "CoreMinimal.h"
#include "ScoreWidgetInterface.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"


UCLASS()
class SKATEBOARDING_API UScoreWidget : public UUserWidget, public IScoreWidgetInterface
{
public:
	virtual void SetScore_Implementation(const FString &TextToDisplay) override;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ScoreText;
	
private:
	GENERATED_BODY()
};
