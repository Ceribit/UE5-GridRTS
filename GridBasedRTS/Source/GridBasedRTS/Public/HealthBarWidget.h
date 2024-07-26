// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRIDBASEDRTS_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SetBarValuePercent(float const value);
	void SetBarColor(FColor Color);

//private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HealthValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBorder* HealthValueBorder;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor BarColor;

};
