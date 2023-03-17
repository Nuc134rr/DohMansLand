#pragma once

class TANKGAMELOADING_API ITankGameLoadingModule : public IModuleInterface
{
public:
	virtual void startLoading(int WinnerID) = 0;
};