// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectInterface.h"

// Add default functionality here for any ISelectInterface functions that are not pure virtual.

void ISelectInterface::MarqueePressed() {}
void ISelectInterface::MarqueeReleased() {}
void ISelectInterface::MarqueeHeld() {}
void ISelectInterface::SelectUnit() {}
void ISelectInterface::DeselectUnit() {}
void ISelectInterface::UnitMoveCommand(FVector Location) {}
TArray<ADefaultCharacter*> ISelectInterface::GrabSelectedUnits() { return TArray<ADefaultCharacter*>(); }

