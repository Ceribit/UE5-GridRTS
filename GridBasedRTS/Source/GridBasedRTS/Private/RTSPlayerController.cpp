// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "MarqueeHUD.h"
#include "DefaultCharacter.h"
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

void ARTSPlayerController::RightMouseButtonPressed() {
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_EngineTraceChannel4, false, HitResult)) {
		FVector HitLocation = HitResult.Location;
		if (AMarqueeHUD* hud = Cast<AMarqueeHUD>(GetHUD())) {
			TArray<ADefaultCharacter*> SelectedActors = hud->GrabSelectedUnits();
			int LocationXOffset = 0;
			int LocationYOffset = 0
			;
			for (ADefaultCharacter* SelectedCharacter : SelectedActors) {
				SelectedCharacter->UnitMoveCommand(FVector(HitLocation.X + LocationXOffset, HitLocation.Y + LocationYOffset, HitLocation.Z));
				LocationYOffset += 40;
				if (LocationYOffset == 160) {
					LocationYOffset = 0;
					LocationXOffset += 40;
				}
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Movement Location at: %s"), *HitLocation.ToString());

	}
}

void ARTSPlayerController::SetupInputComponent() {
	ARTSPlayerController::Super::SetupInputComponent();
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ARTSPlayerController::LeftMouseButtonPressed);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ARTSPlayerController::LeftMouseButtonReleased);
	InputComponent->BindKey(EKeys::RightMouseButton, IE_Released, this, &ARTSPlayerController::RightMouseButtonPressed);


}

