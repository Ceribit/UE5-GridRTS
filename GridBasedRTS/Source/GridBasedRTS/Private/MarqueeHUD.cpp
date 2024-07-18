// Fill out your copyright notice in the Description page of Project Settings.


#include "MarqueeHUD.h"

AMarqueeHUD::AMarqueeHUD() {

}

void AMarqueeHUD::MarqueePressed() {
	IsDrawing = true;
	float LocationX = 0, LocationY = 0;
	GetOwningPlayerController()->GetMousePosition(LocationX, LocationY);
	StartMousePosition = FVector2D(LocationX, LocationY);
}

void AMarqueeHUD::MarqueeHeld() {
	float LocationX = 0, LocationY = 0;
	GetOwningPlayerController()->GetMousePosition(LocationX, LocationY);
	CurrentMousePosition = FVector2D(LocationX, LocationY);
}

void AMarqueeHUD::MarqueeReleased() {
	IsDrawing = false;
	UE_LOG(LogTemp, Warning, TEXT("Deleting %d actors"), SelectedActors.Num());

	for (ADefaultCharacter* Character : SelectedActors) {
		Character->DeselectUnit();
	}
	SelectedActors.Reset();
}


void AMarqueeHUD::DrawHUD(){
	if (IsDrawing) {
		DrawRect(FLinearColor(0.f, 0.f, 0.5f, 0.3f), StartMousePosition.X, StartMousePosition.Y, CurrentMousePosition.X - StartMousePosition.X, CurrentMousePosition.Y - StartMousePosition.Y);
	}
	TArray<ADefaultCharacter*> OutActors;
	if (GetActorsInSelectionRectangle(StartMousePosition, CurrentMousePosition, OutActors, false)) {

		for (ADefaultCharacter* Actor : OutActors) {
			Actor->SelectUnit();
			SelectedActors.AddUnique(Actor);
			ActorsInRectangle.AddUnique(Actor);
		}

		for (ADefaultCharacter* Actor : ActorsInRectangle) {
			if (OutActors.Find(Actor) == -1) {
				Actor->DeselectUnit();
			}
		}
	}
	

	
}