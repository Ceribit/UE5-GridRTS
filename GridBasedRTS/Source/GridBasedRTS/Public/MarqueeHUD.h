// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SelectInterface.h"
#include "DefaultCharacter.h"
#include "MarqueeHUD.generated.h"

/**
 * 
 */
UCLASS()
class GRIDBASEDRTS_API AMarqueeHUD : public AHUD, public ISelectInterface
{
	GENERATED_BODY()
	
public:
	AMarqueeHUD();
	virtual void MarqueePressed() override;
	virtual void MarqueeReleased() override;
	virtual void MarqueeHeld() override;
	virtual void DrawHUD() override;


	bool IsDrawing = false;

	FVector2D StartMousePosition;
	FVector2D CurrentMousePosition;

	TArray<ADefaultCharacter*> SelectedActors;
	TArray<ADefaultCharacter*> ActorsInRectangle;


};