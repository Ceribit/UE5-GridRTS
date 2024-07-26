// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "MarqueeHUD.h"
#include "DefaultCharacter.h"
#include "SelectInterface.h"
#include <algorithm>

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
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_EngineTraceChannel2, true, HitResult)) {
		FVector HitLocation = HitResult.Location;


		UE_LOG(LogTemp, Warning, TEXT("Actor hit:  %s"), *HitResult.GetActor()->GetName());
		if (AHexagonalGrid* grid = Cast<AHexagonalGrid>(HitResult.GetActor())) {
			FIntPoint Index = grid->GetTileIndexFromMousePosition(HitLocation);
			HitLocation = grid->TileDataMap.Find(Index)->Transform.GetLocation();


			if (AMarqueeHUD* hud = Cast<AMarqueeHUD>(GetHUD())) {
				TArray<ADefaultCharacter*> SelectedActors = hud->GrabSelectedUnits();
				int TotalUnits = SelectedActors.Num();
				int GridLength = std::max(3, static_cast<int>(ceil(sqrt(TotalUnits))));
				for (ADefaultCharacter* SelectedCharacter : SelectedActors) {
					int LocationXOffset = 0;
					int LocationYOffset = 0;

					FIntPoint UnitLocation = grid->GetTileIndexFromMousePosition(SelectedCharacter->GetActorLocation());
					UE_LOG(LogTemp, Warning, TEXT("Moving Actor from {%d , %d}"), UnitLocation.X, UnitLocation.Y);

					SelectedCharacter->UnitMoveCommand(FVector(HitLocation.X + LocationXOffset, HitLocation.Y + LocationYOffset, HitLocation.Z));
				}
			}
			FIntPoint Destination = grid->GetTileIndexFromMousePosition(HitLocation);

			UE_LOG(LogTemp, Warning, TEXT("Moving Actors To at: %s {%d,%d}"), *HitLocation.ToString(), Destination.X, Destination.Y);
		}

	}
}

void ARTSPlayerController::SetupInputComponent() {
	ARTSPlayerController::Super::SetupInputComponent();
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ARTSPlayerController::LeftMouseButtonPressed);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ARTSPlayerController::LeftMouseButtonReleased);
	InputComponent->BindKey(EKeys::RightMouseButton, IE_Released, this, &ARTSPlayerController::RightMouseButtonPressed);


}

