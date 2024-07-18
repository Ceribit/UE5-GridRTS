// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SelectInterface.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARTSPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;


	//virtual void MarqueePressed() override;
	//virtual void MarqueeReleased() override;
	//virtual void MarqueeHeld() override;


	//class RTSInterface : public UBaseInterface {
	//};
	UFUNCTION()
	void LeftMouseButtonPressed();

	UFUNCTION()
	void LeftMouseButtonReleased();

	bool IsLeftMousePressed;

};
