// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class TANKGAMELOADING_API STransitionWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STransitionWidget){}

	//Slate parameter so we can get the winner
	SLATE_ARGUMENT(int, WinnerID);

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	//Sets our brush's resource path (loaded in later when setting brush resource)
	void SetWinnerResource(int ID);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	TOptional<FTransform2D> STransitionWidget::SetPaperTransform(FVector2D NewPosition);

private:
	FName winnerResourcePath;
	TOptional<FTransform2D> PaperTransform;
};

