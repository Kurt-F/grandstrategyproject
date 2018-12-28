#pragma once
#include "Util.h"
#include "Unit.h"

class ArmyManagerSingleton
{
private:
	// In OpenCL structs should be use instead of Unit objects
	struct Engagement {
		float* att_modifiers;
		float* def_modifiers;
		int num_att_mods;
		int num_def_mods;
		Unit* attacker;
		Unit* defender;
	};
	static int num_engagements;
	static ArmyManagerSingleton* instance;
	Engagement* engagements; 
	ArmyManagerSingleton();
	~ArmyManagerSingleton();
public:
	bool Resolve_Engagements(); // Returns false if no engagements
	void AddEngagement(Unit* a, Unit* d);
	static ArmyManagerSingleton* Get_Instance();
};

