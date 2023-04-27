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

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


//Creating our widget
void STransitionWidget::Construct(const FArguments& InArgs)
{

    //Allows us to edit outside of construct
    BaseOverlay = SNew(SOverlay);
    FSlateFontInfo DohFontInfo;

 	ChildSlot
	[
		SAssignNew(BaseOverlay, SOverlay)
        + SOverlay::Slot()
        [
            SNew(SPaperWithWinner)
            .WinnerColor(InArgs._WinnerColor)
            .WinnerText(InArgs._WinnerText)
        ]
        + SOverlay::Slot()
        .VAlign(VAlign_Center)
        .HAlign(HAlign_Right)
        [
            SNew(SImage)
            .Image(FDeferredCleanupSlateBrush::CreateBrush(LoadObject<UTexture>(NULL, TEXT("/Game/Assets/Textures/UI/Transition_Plane.Transition_Plane"))).Get().GetSlateBrush())
        ]
	];

    ViewportHandle = GEngine->GameViewport->Viewport->ViewportResizedEvent.AddRaw(this, &STransitionWidget::SetViewportBasedVariables);
    SetViewportBasedVariables(NULL, 0);
}

void STransitionWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
    SWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
    LerpTime += InDeltaTime / TimeToTransition;
    BaseOverlay.Get()->SetRenderTransform(TOptional<FSlateRenderTransform>(FMath::Lerp(StartingPosition, EndPosition, LerpTime)));
}

void STransitionWidget::SetViewportBasedVariables(FViewport* Viewport, uint32 val)
{
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    StartingPosition = FVector2D(-ViewportSize.X, 0);
    EndPosition = FVector2D(ViewportSize.X, 0);
}


void STransitionWidget::SPaperWithWinner::Construct(const FArguments& InArgs)
{
    //Variable that we can edit on tick
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
    if(PaperOverlay->GetChildren()->Num() > 2)
    {
        PaperOverlay->GetChildren()->GetChildAt(0).Get().SetRenderTransform(FindStartingTransform(FVector2D(1, 1.41), FVector2D(0, -ViewportSize.Y / 2), ViewportSize));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Array is too small, did not update."))
    return;
}

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


STransitionWidget::~STransitionWidget()
{
    GEngine->GameViewport->Viewport->ViewportResizedEvent.Remove(ViewportHandle);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
