// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetRelativeRotation(FRotator(0.f, 0.0f, 0.f));
	SelectionDecal->SetRelativeLocation(FVector(0.f, 0.0f, -70.f));
	SelectionDecal->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
	//SelectionDecal->DecalSize = FVector(30.f, 30.f, 15.f);
	SelectionDecal->SetupAttachment(RootComponent);

	GetMesh()->bReceivesDecals = false;
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADefaultCharacter::SelectUnit()
{
	SelectionDecal->SetVisibility(true);
}

void ADefaultCharacter::DeselectUnit()
{
	SelectionDecal->SetVisibility(false);
}
