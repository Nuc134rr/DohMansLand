
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
        loadingScreen.bAutoCompleteWhenLoadingCompletes = false;
        loadingScreen.bWaitForManualStop = true;
        loadingScreen.WidgetLoadingScreen = SNew(STransitionWidget).WinnerColor(Color).WinnerText(TextToDisplay);
        //Actually add to the screen
        GetMoviePlayer()->SetupLoadingScreen(loadingScreen);
    }

    //Stops the movie (currently unfinished)
    void stopLoading()
    {
        GetMoviePlayer()->StopMovie();
    }
};

IMPLEMENT_MODULE(FTankGameLoadingModule, TankGameLoading);

