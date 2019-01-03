#pragma once
#include <string>
#define NUM_EQUIPMENT_TYPES 25;

class Unit
{
private:
	float attack;
	float air_attack;
	float ew;
	float armour;
	float air_cntr;
	float ew_cntr;
	float strength;
	float max_strength;
	int attack_width;
	int* max_equipment;
	int* equipment;
	float speed;
	std::string name;

public:
	Unit(
		float att,
		float air_att,
		float ew,
		float armour, 
		float air_cntr,
		float ew_cntr,
		int a_width,
		int* max_e,
		int* e,
		float s
	);
	~Unit();
	void Take_Damage(float amount);

};

