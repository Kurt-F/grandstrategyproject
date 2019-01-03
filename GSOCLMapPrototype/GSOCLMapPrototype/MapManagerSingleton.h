#pragma once
#include "Map_Node.h"
class MapManagerSingleton
{
private:
	static MapManagerSingleton* instance;
	Map_Node* map;
	MapManagerSingleton();
	~MapManagerSingleton();
public: 
	static MapManagerSingleton Get_Instance();
	bool Create_Connection(Map_Node a, Map_Node b);
	bool Add_Node(Map_Node m);
};

