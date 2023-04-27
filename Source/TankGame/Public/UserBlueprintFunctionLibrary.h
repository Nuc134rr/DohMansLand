// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API UUserBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
    
    //Plus Equal float and int

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Int += Int", CompactNodeTitle = "+=", Keywords = "+ plus equal add", Category = "Utilities | Operators"))
    static void plusEqual_Int(UPARAM(ref) int &A, int Amount,UPARAM(DisplayName = "Result (Not Referencable)") int &a_out);
    
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Float += Float", CompactNodeTitle = "+=", Keywords = "+ plus equal add", Category = "Utilities | Operators"))
    static void plusEqual_Float(UPARAM(ref) float &A, float Amount,UPARAM(DisplayName = "Result (Not Referencable)") float &a_out);

    //Creates an asynchronus loading screen
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Loading Screen", Keywords = "load loading screen"))
    static void CreateLoadScreen(FString TextToDisplay, FLinearColor Color);
    
};
