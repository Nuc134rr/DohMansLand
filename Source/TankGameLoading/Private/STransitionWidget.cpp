// Fill out your copyright notice in the Description page of Project Settings.


#include "STransitionWidget.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SlateOptMacros.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Slate/WidgetTransform.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "TankGameLoadingModule.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


//Creating our widget
void STransitionWidget::Construct(const FArguments& InArgs)
{

    //Allows us to edit outside of construct
    BaseOverlay = SNew(SOverlay);
    FSlateFontInfo DohFontInfo;
    FirstPaper = SNew(SPaperWithWinner);

 	ChildSlot
	[
		SAssignNew(BaseOverlay, SOverlay)
        + SOverlay::Slot()
        [
            SAssignNew(FirstPaper, SPaperWithWinner)
            .WinnerColor(InArgs._WinnerColor)
            .WinnerText(InArgs._WinnerText)
        ]
        + SOverlay::Slot()
        [
            //Second paper for looping
            SAssignNew(SecondPaper, SPaperWithWinner)
            .WinnerColor(InArgs._WinnerColor)
            .WinnerText(InArgs._WinnerText)
        ]
        + SOverlay::Slot()
        //WIP
        .VAlign(VAlign_Center)
        .HAlign(HAlign_Right)
        [
            SNew(SImage)
            .Image(FDeferredCleanupSlateBrush::CreateBrush(LoadObject<UTexture>(NULL, TEXT("/Game/Assets/Textures/UI/Transition_Plane.Transition_Plane"))).Get().GetSlateBrush())
        ]
	];

    //Set a function delegate to theoretically run when the viewport changes size
    ViewportHandle = GEngine->GameViewport->Viewport->ViewportResizedEvent.AddRaw(this, &STransitionWidget::SetViewportBasedVariables);
    SetViewportBasedVariables(NULL, 0);

    //Sets the starting transform
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    BaseOverlay.Get()->SetRenderTransform(TOptional<FSlateRenderTransform>(FVector2D(-ViewportSize.X, 0)));

}

void STransitionWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
    SWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

    //Tries to get the current position of the widget: or 0,0 if un-set
    FVector2D CurrentRenderTransform = BaseOverlay.Get()->GetRenderTransform().Get(FVector2D(0, 0)).GetTranslation();
    //Adds to the current position moving from left to right
    BaseOverlay.Get()->SetRenderTransform(TOptional<FSlateRenderTransform>(FVector2D(CurrentRenderTransform.X + (TimeToTransition * InDeltaTime), CurrentRenderTransform.Y)));

    //Checks if our second paper is in the middle of the screen.
    if(SecondPaper.Get()->GetRenderTransform().IsSet() == true && BaseOverlay.Get()->GetRenderTransform().IsSet() == true && CurrentTime < 20)
    {
        if(SecondPaper.Get()->GetRenderTransform().GetValue().GetTranslation().X + BaseOverlay.Get()->GetRenderTransform().GetValue().GetTranslation().X > 0)
        {
            //Resets the BaseOverlay to have a looping effect
            BaseOverlay.Get()->SetRenderTransform(TOptional<FSlateRenderTransform>(FVector2D(0, 0)));
        }
    }

    //Removes the loading screen (does not work yet)
    if(CurrentTime > 20)
    {
        ITankGameLoadingModule* screen = FModuleManager::LoadModulePtr<ITankGameLoadingModule>("TankGameLoading");
        if(screen != NULL)
        {
            screen->stopLoading();
        }
    }
    CurrentTime += InDeltaTime;
}

//Runs on viewport changing size
void STransitionWidget::SetViewportBasedVariables(FViewport* Viewport, uint32 val)
{
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);

    //Runs on children for them to update
    FirstPaper.Get()->UpdateVariables(ViewportSize);
    SecondPaper.Get()->UpdateVariables(ViewportSize);

    //Sets the second paper's position right behind the first
    FVector2D FirstPaperPosition = FirstPaper.Get()->GetRenderTransform().Get(FSlateRenderTransform(FVector2D(0, 0))).GetTranslation();
    SecondPaper.Get()->SetRenderTransform(TOptional<FSlateRenderTransform>(FVector2D(FirstPaperPosition.X - (ViewportSize.X), 0)));
}


//Construct for our paper widget
void STransitionWidget::SPaperWithWinner::Construct(const FArguments& InArgs)
{
    //Variable that we can edit
    PaperOverlay = SNew(SOverlay);

    ChildSlot
    [
        SAssignNew(PaperOverlay, SOverlay)
        + SOverlay::Slot()
        .VAlign(VAlign_Center)
        .HAlign(HAlign_Center)
        [
            //Paper
            SNew(SImage)
            .Image(FDeferredCleanupSlateBrush::CreateBrush(LoadObject<UTexture>(NULL, TEXT("/Game/Assets/Textures/UI/Transition_Paper.Transition_Paper"))).Get().GetSlateBrush())
        ]
        + SOverlay::Slot()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            //Winner text
            SNew(STextBlock)
            .ShadowColorAndOpacity(FLinearColor::Black)
            .ColorAndOpacity(FSlateColor(InArgs._WinnerColor))
            .ShadowOffset(FIntPoint(-1, 1)) 
            .Font(FSlateFontInfo(LoadObject<UObject>(NULL, TEXT("/Game/UI/font/DohMansFont-Regular_Font.DohMansFont-Regular_Font")), 100))
            .Text(FText::FromString(InArgs._WinnerText)) 
            .Justification(ETextJustify::Center)
        ]
    ];
}

//Only updates the children of PaperOverlay
void STransitionWidget::SPaperWithWinner::UpdateVariables(FVector2D ViewportSize)
{
    //Prevents us from crashing
    if(PaperOverlay->GetChildren()->Num() > 0)
    {
        //Sets scale and starting transform. For some reason Unreal's slate alignment doesn't work.
        PaperOverlay->GetChildren()->GetChildAt(0).Get().SetRenderTransform(FindStartingTransform(FVector2D(1, 1.41), FVector2D(0, -ViewportSize.Y / 2), ViewportSize));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Array is too small, did not update."))
    return;
}

/*
Finds the scale necessary for a square image that has been stretched by the viewport. 
It also returns the TOptional<FSlateRenderTransform> so we take in a new position to return attatched to the return value.
This return value type is required for updating slate transform.
*/
TOptional<FSlateRenderTransform> STransitionWidget::SPaperWithWinner::FindStartingTransform(FVector2D CurrentScale, FVector2D NewPosition, FVector2D ViewportSize)
{
    //Determine which value we want to base the other off
    if(ViewportSize.X > ViewportSize.Y)
    {
        return TOptional<FSlateRenderTransform>(FTransform2D(FScale2D(CurrentScale.X, CurrentScale.Y * (ViewportSize.X / ViewportSize.Y)), NewPosition));
    }
    else if(ViewportSize.X < ViewportSize.Y)
    {
        return TOptional<FSlateRenderTransform>(FTransform2D(FScale2D(CurrentScale.X * (ViewportSize.Y / ViewportSize.X), CurrentScale.Y), NewPosition));
    }

    return TOptional<FSlateRenderTransform>(FTransform2D(FScale2D(CurrentScale.X, CurrentScale.Y), NewPosition));
}

//Removes the delegate references
STransitionWidget::~STransitionWidget()
{
    GEngine->GameViewport->Viewport->ViewportResizedEvent.Remove(ViewportHandle);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
