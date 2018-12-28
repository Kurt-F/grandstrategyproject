#pragma once
#include "Util.h"
#include "Unit.h"

class Army
{
private:
	int units_in_army;
	Unit* units;
	char* name;
public:
	Army();
	~Army();
	// Returning false -> unit unsuccesfully added
	bool Add_Unit(Unit u);
};

