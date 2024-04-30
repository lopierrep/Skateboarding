

#include "ScoreWidget.h"


#include "Components/TextBlock.h"


void UScoreWidget::SetScore(FString TextToDisplay)
{
	if (TextToDisplay.IsEmpty()) return;
	ScoreText->SetText(FText::FromString(TextToDisplay));
}

