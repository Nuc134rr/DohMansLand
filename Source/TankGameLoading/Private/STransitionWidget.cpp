// Fill out your copyright notice in the Description page of Project Settings.


#include "STransitionWidget.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SlateOptMacros.h"
#include "Slate/DeferredCleanupSlateBrush.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STransitionWidget::SetWinnerResource(int ID)
{
    //Yes, this is unfortunatly how I'm doing this
    switch(ID)
    {
        //Red
        case 0 :
            winnerResourcePath = TEXT("/Game/Assets/Textures/UI/Red_WinsTEX.Red_WinsTEX");
        break;
        //Orange
        case 1:
            winnerResourcePath = TEXT("/Game/Assets/Textures/UI/Orange_WinsTEX.Orange_WinsTEX");
        break;
        //Yellow
        case 2:
            winnerResourcePath = TEXT("/Game/Assets/Textures/UI/Yellow_WinsTEX.Yellow_WinsTEX");
        break;
        //Green
        case 3:
            winnerResourcePath = TEXT("/Game/Assets/Textures/UI/Green_WinsTEX.Green_WinsTEX");
        break;
        //Blue
        case 4:
            winnerResourcePath = TEXT("/Game/Assets/Textures/UI/Blue_WinsTEX.Blue_WinsTEX");
        break;
        //Purple
        case 5:
            winnerResourcePath = TEXT("/Game/Assets/Textures/UI/Purple_WinsTEX.Purple_WinsTEX");
        break;
        //Default
        default:
            winnerResourcePath = TEXT("/Game/Assets/Textures/UI/Purple_WinsTEX.Purple_WinsTEX");
        break;
    }
}

void STransitionWidget::Construct(const FArguments& InArgs)
{
    
    //Set variable to feed into slate's construction
    SetWinnerResource(InArgs._WinnerID);
    GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Path = %s"), *winnerResourcePath.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Path = %s") , *winnerResourcePath.ToString())
 	ChildSlot
	[
		SNew(SOverlay)
        + SOverlay::Slot()
        .VAlign(VAlign_Fill)
        .HAlign(HAlign_Fill)
        [
            //Winner Image
            SNew(SImage)
            .RenderTransform(this, )
            //FDeferredCleanupSlateBrush seems to be required when using Movie Player's loading screen
            .Image(FDeferredCleanupSlateBrush::CreateBrush(LoadObject<UTexture>(NULL, *winnerResourcePath.ToString())).Get().GetSlateBrush())
        ]
	];
}

void STransitionWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{

    SWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

    UE_LOG(LogTemp, Warning, TEXT("TickRunning"))
    GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, TEXT("Tick Ran"));
}

const TOptional<FTransform2D> STransitionWidget::SetPaperTransform(FVector2D NewPosition) const
{
    if(PaperTransform.IsSet()) //Making sure we aren't setting a value that doesn't exist
    {
        PaperTransform.GetValue().SetTranslation(NewPosition);
    }
    else
    {
        PaperTransform = TOptional<FSlateRenderTransform>(FSlateRenderTransform(NewPosition));
    }
    return PaperTransform;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
