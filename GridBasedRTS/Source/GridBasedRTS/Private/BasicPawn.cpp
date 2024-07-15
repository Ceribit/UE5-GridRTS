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

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	//SpringArmComp->SetWorldLocation(FVector(0, 0, 0));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->SetRelativeRotation(FRotator(-45.f, 0.0f, 0.f));

	//GetRootComponent()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	SpringArmComp->TargetArmLength = 700.0f;
	SpringArmComp->bEnableCameraLag = true;
	DesiredArmLength = 700.0f;
	ZoomStrength = 100.0f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	
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

void ABasicPawn::EnhancedInputZoom(const FInputActionValue& Value)
{
	if (GEngine) {
		const float CurrentValue = Value.Get<float>();
		DesiredArmLength = FMath::Clamp(SpringArmComp->TargetArmLength + CurrentValue * ZoomStrength, 300.f, 2000.f);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Zoom Change: " + FString::FromInt(DesiredArmLength)));
		//DesiredRotation += FRotator(0, CurrentValue*20, 0);
		
		//DesiredRotation = FRotator(DesiredRotation.Pitch, DesiredRotation.Yaw, DesiredRotation)
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

		//SetActorLocation(FVector(0, 0, 0));
		SpringArmComp->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));
		DesiredLocation = FVector(0.0f,0.f,100.0f);
		DesiredRotation = SpringArmComp->GetRelativeRotation();

	}
}

// Called every frame
void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Update Camera 
	float FinalArmLength = FMath::FInterpTo(SpringArmComp->TargetArmLength, DesiredArmLength, DeltaTime, 5.0f);
	SpringArmComp->TargetArmLength = FinalArmLength;

	// Update Camera position
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
	enhancedInputComponent->BindAction(inputToZoom, ETriggerEvent::Triggered, this, &ABasicPawn::EnhancedInputZoom);

	

}

