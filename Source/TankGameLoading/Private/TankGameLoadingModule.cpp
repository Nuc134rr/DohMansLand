
#include "TankGameLoadingModule.h"
#include "MoviePlayer.h"
#include "STransitionWidget.h"

class FTankGameLoadingModule : public ITankGameLoadingModule
{
    public:
    void startLoading(int WinnerID) override
    {
        FLoadingScreenAttributes loadingScreen;
        loadingScreen.bAutoCompleteWhenLoadingCompletes = true;
        loadingScreen.MinimumLoadingScreenDisplayTime = 2.f;
        loadingScreen.WidgetLoadingScreen = SNew(STransitionWidget).WinnerID(WinnerID);
        GetMoviePlayer()->SetupLoadingScreen(loadingScreen);
    }
};

IMPLEMENT_MODULE(FTankGameLoadingModule, TankGameLoading);

