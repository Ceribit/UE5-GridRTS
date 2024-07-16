// Fill out your copyright notice in the Description page of Project Settings.


#include "TileData.h"

FTileData::FTileData(FIntPoint NewIndex, FTransform NewTransform) {
	TileState = UTileState::NONE;
	Index = NewIndex;
	Transform = NewTransform;
}
