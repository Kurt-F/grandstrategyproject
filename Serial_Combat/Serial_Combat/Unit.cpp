#include "pch.h"
#include "Unit.h"
#include "ArmyManagerSingleton.h"
#include <iostream>

Unit::Unit() {}

Unit::Unit(float* attr, std::string n)
{
	this->flags = 0;
	name = n;
	this->attributes = attr;
}


Unit::~Unit()
{
	std::cout << "A unit has been deleted! This is a test message." << std::endl;
}

// Create an engagement 
void Unit::Engage(Unit* defender)
{
	ArmyManagerSingleton* manager = ArmyManagerSingleton::Get_Instance();
	manager->AddEngagement(this, defender);
}

void Unit::Take_Damage(int type, float amount) {
	if (type == STRENGTH) {
		this->attributes[STRENGTH] -= amount;
		// In terms of opencl, this should be done differently
		if (this->attributes[STRENGTH] <= 0) {
			this->attributes[STRENGTH] = 0;
			this->Set_Flag(UNIT_DEAD);
			std::cout << "A unit has died!" << std::endl;
		}
	}
	else if (type == MORALE) {
		this->attributes[MORALE] -= amount;
		if (this->attributes[MORALE] <= 0) 
		{
			this->attributes[MORALE] = 0;
			this->Set_Flag(UNIT_RETREAT);
			std::cout << "A unit has retreated!" << std::endl;
		}

	}
}

void Unit::Add_Experience(float amount) {
	// TODO: Levelling. Each integer being a level and experience gains mostly fractional maybe.
	this->attributes[EXPERIENCE] += amount;
}

float Unit::Get_Attribute(int i)
{
	return this->attributes[i];
}

std::string Unit::Get_Name() {
	return this->name;
}

std::string Unit::To_String() {
	return "Unit \"" + (std::string) (this->name) + "\"";
}

void Unit::Set_Flag(unsigned char flag)
{
	this->flags = flags | flag;
}

bool Unit::Check_Flag(unsigned char flag) 
{
	std::cout << flags;
	unsigned char test = this->flags;
	test = test & flag;
	if ((this->flags & flag) > 0) 
	{
		return true;
	}
	return false;
}