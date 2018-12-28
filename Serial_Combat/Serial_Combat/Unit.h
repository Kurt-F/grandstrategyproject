#pragma once
#include <string>
class Unit
{
private:
	float* attributes;
	std::string name; // This is irrelevant for OpenCL purposes
	unsigned char flags;
public:
	Unit();
	Unit(float* attr, std::string n);
	~Unit();
	// Creates an engagement in the ArmyManagerSingleton
	void Engage(Unit* defender);
	float Get_Attribute(int i);
	void Take_Damage(int type, float amount);
	void Add_Experience(float amount);
	void Set_Flag(unsigned char f);
	bool Check_Flag(unsigned char f);
	std::string Get_Name();
	std::string To_String();
};

