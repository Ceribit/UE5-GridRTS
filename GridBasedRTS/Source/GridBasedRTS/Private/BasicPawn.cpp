// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"
#include "RTSPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
// Sets default values
ABasicPawn::ABasicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
}

void ABasicPawn::EnhancedInputMoveRight(const FInputActionValue& Value)
{
	if (GEngine) {
		const float CurrentValue = Value.Get<float>();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Move vector: " + FString::FromInt(CurrentValue)));
		DesiredLocation += FVector(0, CurrentValue * 20, 0);
	}
}

void ABasicPawn::EnhancedInputMoveForward(const FInputActionValue& Value)
{
	if (GEngine) {
		const float CurrentValue = Value.Get<float>();
		DesiredLocation += FVector(CurrentValue * 20, 0, 0);
	}
}


// Called when the game starts or when spawned
void ABasicPawn::BeginPlay()
{
	Super::BeginPlay();
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(GetController());
	if (PlayerController) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Controllered retrieved."));
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(inputMappingContext, 0);
		DesiredLocation = GetActorLocation();
	}
}

// Called every frame
void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActorLocation = GetActorLocation();
	FVector Destination = FMath::VInterpTo(ActorLocation, DesiredLocation, DeltaTime, 5.0f);
	SetActorLocation(Destination);

}

// Called to bind functionality to input
void ABasicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	enhancedInputComponent->BindAction(inputToMoveRight, ETriggerEvent::Triggered, this, &ABasicPawn::EnhancedInputMoveRight);
	enhancedInputComponent->BindAction(inputToMoveForward, ETriggerEvent::Triggered, this, &ABasicPawn::EnhancedInputMoveForward);

	

}

