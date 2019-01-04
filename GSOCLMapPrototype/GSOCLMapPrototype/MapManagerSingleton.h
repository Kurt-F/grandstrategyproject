#pragma once
#include "Map_Node.h"
class MapManagerSingleton
{
private:
	static MapManagerSingleton* instance;
	Map_Node** map;
	MapManagerSingleton();
	~MapManagerSingleton();
public: 
	static MapManagerSingleton* Get_Instance();
	bool Create_Connection(Map_Node &a, Map_Node &b, int freight_cost_per_lb = 0, int travel_cost = 0);
	bool Remove_Connection(Map_Node &a, Map_Node &b);
	bool Add_Node(Map_Node *m);
	Map_Node* Get_Node(int index);
	bool Remove_Node(int index);
	void Save_Map();
	bool Load_Map();
};

