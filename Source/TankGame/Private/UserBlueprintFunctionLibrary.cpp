// Fill out your copyright notice in the Description page of Project Settings.


#include "UserBlueprintFunctionLibrary.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "TankGameLoadingModule.h"

void UUserBlueprintFunctionLibrary::plusEqual_Int(int &A, int Amount, int &a_out)
{
    A += Amount;
    a_out = A;
}

void UUserBlueprintFunctionLibrary::plusEqual_Float(float &A, float Amount, float &a_out)
{
    A += Amount;
    a_out = A;
}

void UUserBlueprintFunctionLibrary::CreateLoadScreen(int Winner)
{
    ITankGameLoadingModule* screen = FModuleManager::LoadModulePtr<ITankGameLoadingModule>("TankGameLoading");
    if(screen != NULL)
    {
        screen->startLoading(Winner);
    }
}
