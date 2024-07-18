// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "MarqueeHUD.h"
#include "SelectInterface.h"

ARTSPlayerController::ARTSPlayerController() {

}

void ARTSPlayerController::BeginPlay() {
	APlayerController::Super::BeginPlay();
}



void ARTSPlayerController::Tick(float DeltaTime)
{
	APlayerController::Super::Tick(DeltaTime);
	if (IsLeftMousePressed) {
		if (AMarqueeHUD* hud = Cast<AMarqueeHUD>(GetHUD())) {
			hud->MarqueeHeld();
		}
	}

}



void ARTSPlayerController::LeftMouseButtonPressed() {
	IsLeftMousePressed = true;
	if (AMarqueeHUD* hud = Cast<AMarqueeHUD>(GetHUD())) {
		hud->MarqueePressed();
	}
}

void ARTSPlayerController::LeftMouseButtonReleased() {
	IsLeftMousePressed = false;
	if (AMarqueeHUD* hud = Cast<AMarqueeHUD>(GetHUD())) {
		hud->MarqueeReleased();
	}
}

void ARTSPlayerController::SetupInputComponent() {
	ARTSPlayerController::Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ARTSPlayerController::LeftMouseButtonPressed);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ARTSPlayerController::LeftMouseButtonReleased);

}

