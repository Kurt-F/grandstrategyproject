#pragma once
#include "Population.h"	
#include "Map_Node.h"
// Singleton for managing populations
class PopManager
{
private:
	PopManager();
	~PopManager();
	void Resolve_Needs(Population p);
	void Resolve_Production(Population p);
	void Resolve_Migration(Population p);
public:
	PopManager Get_Instance();
	void Advance_Day();

};

