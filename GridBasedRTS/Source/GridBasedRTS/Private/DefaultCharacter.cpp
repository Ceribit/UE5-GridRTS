// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "AIController.h"
#include "Consts.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Block);
	UnitData = FUnitData();
	InitializeUnitDecal();
	InitializeHealthBar();
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
	if (auto const widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject())) {
		widget->SetBarValuePercent(UnitData.Health / UnitData.MaxHealth);

	}

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Interface Implementations
void ADefaultCharacter::SelectUnit()
{
	SelectionDecal->SetVisibility(true);
}

void ADefaultCharacter::DeselectUnit()
{
	SelectionDecal->SetVisibility(false);
}

void ADefaultCharacter::UnitMoveCommand(FVector Location) {
	AAIController* controller =  GetController<AAIController>();
	//controller->StopMovement();
	controller->MoveToLocation(Location);
}

void ADefaultCharacter::SetUnitData(FUnitData NewUnitData) {
	UnitData = NewUnitData;
}

ADefaultCharacter* ADefaultCharacter::MAKE(FUnitData UnitData) {
	ADefaultCharacter* NewCharacter = NewObject<ADefaultCharacter>();
	NewCharacter->SetUnitData(UnitData);
	return NewCharacter;
}


void ADefaultCharacter::InitializeHealthBar() {
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue"));

	if (WidgetComponent) {

		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(defs::HealthBarZ);

		// Initialize a widget that was designed with blueprints
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/Core/Player/BP_HealthBar") };
		if (WidgetClass.Succeeded()) {
			WidgetComponent->SetWidgetClass((WidgetClass.Class));
			if (auto widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject())) {
				widget->SetBarValuePercent(100.f);
				//widget->SetBarColor(FColor(0.1f,0.2f,0.3f,1.f));
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Widget failed"));
		}
	}

}
void ADefaultCharacter::UpdateHealthBar() {
	if (auto widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject())) {
		UE_LOG(LogTemp, Warning, TEXT("Setting color to %s"), *UnitData.TeamColor.ToString());
		widget->SetBarColor(UnitData.TeamColor);
	}
}

void ADefaultCharacter::InitializeUnitDecal() {
	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetRelativeRotation(FRotator(0.f, 90.0f, 0.f));
	SelectionDecal->SetRelativeLocation(FVector(0.f, 0.0f, -70.f));
	SelectionDecal->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
	SelectionDecal->SetupAttachment(RootComponent);
	SelectionDecal->SetVisibility(false);


	//SelectionDecal->DecalSize = FVector(30.f, 30.f, 15.f);
	GetMesh()->bReceivesDecals = false;
}

float ADefaultCharacter::GetHealth() const
{
	return UnitData.Health;
}

float ADefaultCharacter::getMaxHealth() const
{
	return UnitData.MaxHealth;
}

void ADefaultCharacter::SetHealth(float const NewHealth)
{
	UnitData.SetHealth(NewHealth);
}
 