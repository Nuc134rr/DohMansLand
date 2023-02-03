// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBaseTank.h"

// Sets default values
ACPPBaseTank::ACPPBaseTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPPBaseTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPPBaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPPBaseTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

