// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class TANKGAMELOADING_API STransitionWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STransitionWidget){}

	//Slate parameter so we can get the winner
	SLATE_ARGUMENT(FString, WinnerText);

	SLATE_ARGUMENT(FLinearColor, WinnerColor);

	//Currently unused, I plan for it to be used but am using TimeToTransition variable instead currenty
	SLATE_ARGUMENT(float, Speed);

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetViewportBasedVariables(FViewport* ViewPort, uint32 val);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	
	float TimeToTransition = 2000.f;

	//Deconstructor for delegate
	~STransitionWidget();
	
private:
	TSharedPtr<SWidget> BaseOverlay;
	
	FDelegateHandle ViewportHandle;
	float CurrentTime = 0.f;

	//A simple paper with the winner shown on top. We need two of these for a loop.
	class SPaperWithWinner: public SCompoundWidget
	{
		public:

		SLATE_BEGIN_ARGS(SPaperWithWinner){}

		//Slate parameter so we can get the winner
		SLATE_ARGUMENT(FString, WinnerText);

		SLATE_ARGUMENT(FLinearColor, WinnerColor);

		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);

		void UpdateVariables(FVector2D ViewportSize);

		static TOptional<FSlateRenderTransform> FindStartingTransform(FVector2D CurrentScale, FVector2D NewPosition, FVector2D ViewportSize);

		private:

		TSharedPtr<SWidget> PaperOverlay;
	};


	TSharedPtr<SPaperWithWinner> FirstPaper;
	TSharedPtr<SPaperWithWinner> SecondPaper;
};

