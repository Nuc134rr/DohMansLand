
#include "TankGameLoadingModule.h"
#include "MoviePlayer.h"
#include "STransitionWidget.h"

class FTankGameLoadingModule : public ITankGameLoadingModule
{
    public:
    virtual void StartupModule() override
    {
        //Pre-load assets
        LoadObject<UTexture>(NULL, TEXT("/Game/Assets/Textures/UI/Transition_Paper.Transition_Paper"));
    }
    void startLoading(FString TextToDisplay, FLinearColor Color) override
    {
        //Setting some relatively self-explanatory variables
        FLoadingScreenAttributes loadingScreen;
        loadingScreen.bAutoCompleteWhenLoadingCompletes = true;
        loadingScreen.MinimumLoadingScreenDisplayTime = 10.f;
        loadingScreen.WidgetLoadingScreen = SNew(STransitionWidget).WinnerColor(Color).WinnerText(TextToDisplay);
        GetMoviePlayer()->SetupLoadingScreen(loadingScreen);

    }
};

IMPLEMENT_MODULE(FTankGameLoadingModule, TankGameLoading);

