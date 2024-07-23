
#include "UnitData.h"

FUnitData::FUnitData() {
	this->Name = "N/A";
	this->Team = "None";
	this->Health = 100;
	this->MaxHealth = 100;
}

FUnitData::FUnitData(FString Name, FString Team, int Health) {
	this->Name = Name;
	this->Team = Team;
	this->Health = Health;
	this->MaxHealth = Health;

}

void FUnitData::SetHealth(float const value)
{
	this->Health = value;
}
