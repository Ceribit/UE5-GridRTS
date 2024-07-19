// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "SelectInterface.h"

#include "DefaultCharacter.generated.h"

UCLASS()
class GRIDBASEDRTS_API ADefaultCharacter : public ACharacter, public ISelectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interface Overrides
	virtual void SelectUnit() override;
	virtual void DeselectUnit() override;
	virtual void UnitMoveCommand(FVector Location) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UDecalComponent* SelectionDecal;

};
