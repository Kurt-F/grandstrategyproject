// Serial_Combat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "ArmyManagerSingleton.h"	
#include <iostream>
#include <string>

int main()
{
	// Setting up some pre-built units			
	// -------------------------------
	std::string Unit_1_Name = "Leg_Infantry";
	float* Unit1 = new float[UNIT_ATTR_COUNT]
	{ 123.0f, 40.0f, 4.0f, 10.0f,
		0.0f, 0.3f, 100.0f, 40.0f,
		15.0f, 123.0f, 0.0f, 0.0f
	};
	// -------------------------------
	int att_army_size = 0;
	int def_army_size = 0;	
	Unit* attacking_units = new Unit[MAX_UNITS_IN_ARMY];
	Unit* defending_units = new Unit[MAX_UNITS_IN_ARMY];
	bool selecting = true;
	while (selecting) {
		if (att_army_size >= 25 && def_army_size >= 25) {
			std::cout << "Maximum number of units selected. ";
			break;
		}
		std::cout << "Please select a unit from the following: " << std::endl;
		std::cout << "1: " << Unit_1_Name << std::endl;
		char selection;
		std::cin >> selection;
		Unit* unit = nullptr;
		if (selection == '1') 
		{
			unit = new Unit(Unit1, Unit_1_Name);
		}
		std::cout << "Is this unit attacking or defending? (1 or 0 respectively)" << std::endl;
		bool stance = false; // false = defending, true = attacking
		std::cin >> stance;
		if (att_army_size >= 25) {
			std::cout << "Attacking army is full, unit assigned to defending army. " << std::endl;
			stance = true;
		}
		else if (def_army_size >= 25) {
			std::cout << "Defending army is full, unit assigned to defending army. " << std::endl;
			stance = false;
		}

		if (stance) {
			// add to attacker army
			attacking_units[att_army_size] = *unit;
			att_army_size++;
		}
		else {
			// add to defender army
			defending_units[def_army_size] = *unit;
			def_army_size++;
		}

		std::cout << "Would you like to add another unit? 1 for yes, 0 for no" << std::endl;
		std::cin >> selecting;
	}
	int num_a = 2;
	int dum_d = 1;
	float* a_mods = new float[2]{ 0.8, 1.1 }; 
	float* d_mods = new float[1]{ 2.3 };
	std::cout << "Starting combat..." << std::endl;
	// Create engagements
	ArmyManagerSingleton* master = ArmyManagerSingleton::Get_Instance();
	for (int i = 0; i < att_army_size; i++) 
	{
		master->AddEngagement(&attacking_units[i], &defending_units[i % att_army_size]);
	}
	// Resolve engagements
	bool ongoing = true;
	while (ongoing)
	{
		std::cout << "Tick" << std::endl;
		ongoing = master->Resolve_Engagements();
	}
	bool winner = false;
	for(int i = 0; i < att_army_size; i++)
	{
		if (!attacking_units[i].Check_Flag(UNIT_DEAD) || !attacking_units[i].Check_Flag(UNIT_RETREAT)) {
			winner = true;
		}
	}
	if (winner) {
		std::cout << "Attacking side won!" << std::endl;
	}
	else
	{
		std::cout << "Defending side won!" << std::endl;
	}
}

