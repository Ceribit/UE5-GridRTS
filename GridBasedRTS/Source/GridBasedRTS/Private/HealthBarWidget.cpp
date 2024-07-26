// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

void UHealthBarWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UHealthBarWidget::SetBarValuePercent(float const value) {
	HealthValue->SetPercent(value);
}

void UHealthBarWidget::SetBarColor(FColor Color) {
	UE_LOG(LogTemp, Warning, TEXT("Setting color to %s"), *HealthValueBorder->GetContentColorAndOpacity().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Setting color to %s"), *Color.ToString());

	//BarColor = Color;
	HealthValueBorder->SetContentColorAndOpacity(Color);
	//HealthValueBorder->GetContentColorAndOpacity(Color);
}
