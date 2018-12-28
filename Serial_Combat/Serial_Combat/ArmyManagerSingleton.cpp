#include "pch.h"
#include "ArmyManagerSingleton.h"
#include "Unit.h"
#include <cstdlib>
#include <random>
#include <iostream>

int ArmyManagerSingleton::num_engagements = 0;
ArmyManagerSingleton* ArmyManagerSingleton::instance;

ArmyManagerSingleton::ArmyManagerSingleton()
{
	// Initialize empty engagements array 
	this->engagements = new Engagement[MAX_NUM_ARMIES * MAX_UNITS_IN_ARMY];
}


ArmyManagerSingleton::~ArmyManagerSingleton()
{
	delete(instance);
}

ArmyManagerSingleton* ArmyManagerSingleton::Get_Instance() 
{
	if (instance == nullptr) 
	{
		instance = new ArmyManagerSingleton();
	}
	return instance;
}

bool ArmyManagerSingleton::Resolve_Engagements()
{
	if (this->num_engagements == 0) {
		return false;
	}
	// TODO: Make actually good algorithm
	for (int i = 0; i < num_engagements; i++) {
		if (&this->engagements[i] == nullptr)
		{
			continue;
		}
		std::cout << num_engagements << std::endl;
		Engagement e = this->engagements[i];
		if (e.defender->Check_Flag(UNIT_DEAD) || e.attacker->Check_Flag(UNIT_DEAD))
		{
			delete(&this->engagements[i]);
			continue;
		}
		// TEMPORARY:
		std::cout << "Starting engagement between " + e.attacker->Get_Name() + " and " + e.defender->Get_Name() + "\n";

		float attack = e.attacker->Get_Attribute(ATTACK);
		float def_attack = e.defender->Get_Attribute(ATTACK);
		float defense = e.defender->Get_Attribute(DEFENSE);
		float att_str = e.attacker->Get_Attribute(STRENGTH) /
			e.attacker->Get_Attribute(MAX_STR);
		float def_str = e.defender->Get_Attribute(STRENGTH) /
			e.defender->Get_Attribute(MAX_STR);
		for (int i = 0; i < e.num_att_mods; i++)
		{
			attack *= e.att_modifiers[i];
			def_attack *= e.att_modifiers[i];
		}
		for (int i = 0; i < e.num_def_mods; i++)
		{
			defense *= e.def_modifiers[i];
		}
		defense *= e.defender->Get_Attribute(TACTICS);
		defense *= e.defender->Get_Attribute(STRENGTH) / e.defender->Get_Attribute(MAX_STR);

		// Calculate defender damage
		float initiative = 0.0f; // Attacker initiative. Unimplemented.
		int num_attacks = 0;
		float def_damage = 0.0f;
		float a_d = attack / defense;
		float d_a = 1 / a_d;
		float prob = 1.0f;
		while (prob >= 0.5f)
		{
			def_damage += attack * a_d * rand();
			prob = rand() + initiative;
		}
		// Calculate attacker damage 
		num_attacks *= 10.0f / e.defender->Get_Attribute(SPEED);
		float att_damage = 0.0f;
		for (int i = 0; i < num_attacks; i++)
		{
			att_damage += def_attack * d_a * rand();
		}
		// Apply all damage to units
		//TODO: Calculate seperate morale and strength damages
		e.defender->Take_Damage(STRENGTH, def_damage);
		e.attacker->Take_Damage(STRENGTH, att_damage);
	}
	delete(&this->engagements);
	this->engagements = new Engagement[MAX_NUM_ARMIES * MAX_UNITS_IN_ARMY];
	this->num_engagements = 0;
	return true;
}

void ArmyManagerSingleton::AddEngagement(Unit* a, Unit* d) 
{
	if (num_engagements >= MAX_NUM_ARMIES * MAX_UNITS_IN_ARMY) 
	{
		return;
	}
	Engagement e;
	e.attacker = a;
	e.defender = d;
	// Placeholder null assignments because modifiers don't exist yet
	e.att_modifiers = nullptr;
	e.def_modifiers = nullptr;
	this->engagements[num_engagements] = e;
	num_engagements++;
}

