// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "SelectInterface.h"
#include "UnitData.h"
#include "HealthBarWidget.h"

#include "DefaultCharacter.generated.h"

UCLASS()
class GRIDBASEDRTS_API ADefaultCharacter : public ACharacter, public ISelectInterface
{
	GENERATED_BODY()

public:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	ADefaultCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interface Overrides
	virtual void SelectUnit() override;
	virtual void DeselectUnit() override;
	virtual void UnitMoveCommand(FVector Location) override;
	
	// Unit Data
	FUnitData UnitData;

	virtual void InitializeUnitDecal();
	virtual void InitializeHealthBar();
	virtual void UpdateHealthBar();

	float GetHealth() const;
	float getMaxHealth() const;
	void SetHealth(float const NewHealth);
	void SetUnitData(FUnitData UnitData);
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Character")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UDecalComponent* SelectionDecal;

};
