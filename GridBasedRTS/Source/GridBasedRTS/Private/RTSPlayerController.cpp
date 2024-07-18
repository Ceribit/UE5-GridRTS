// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"

ARTSPlayerController::ARTSPlayerController() {
	//Super::APlayerController();
}

void ARTSPlayerController::BeginPlay() {
	Super::BeginPlay();

}
void ARTSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsLeftMousePressed) {
		UE_LOG(LogTemp, Warning, TEXT("Left Mouse Button Pressed!"));
	}

}



void ARTSPlayerController::LeftMouseButtonPressed() {
	IsLeftMousePressed = true;
}

void ARTSPlayerController::LeftMouseButtonReleased() {
	IsLeftMousePressed = false;
	UE_LOG(LogTemp, Warning, TEXT("Left Mouse Button Released!"));
}

void ARTSPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ARTSPlayerController::LeftMouseButtonPressed);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ARTSPlayerController::LeftMouseButtonReleased);

}

