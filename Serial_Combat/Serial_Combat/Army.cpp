#include "pch.h"
#include "Army.h"
#include "Unit.h"


Army::Army()
{
	this->units_in_army = 0;
	// For whatever reason I don't quite get how arrays of objects work in C++ so we'll do this
	Unit temp[25]; 
	this->units = temp;
}


Army::~Army()
{
	for (int i = 0; i < MAX_UNITS_IN_ARMY; i++) 
	{
		if (&this->units[i] == nullptr) 
		{
			delete(&units[i]);
		}
	}
}

bool Army::Add_Unit(Unit u)
{
	if (this->units_in_army >= MAX_UNITS_IN_ARMY) {
		return false;
	}
	units_in_army++;
	this->units[units_in_army] = u;
	return true;
}
