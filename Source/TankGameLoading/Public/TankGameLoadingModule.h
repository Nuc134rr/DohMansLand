#pragma once

class TANKGAMELOADING_API ITankGameLoadingModule : public IModuleInterface
{
public:
	virtual void startLoading(FString TextToDisplay, FLinearColor Color) = 0;
	SWindow LoadingWindow;
	
};