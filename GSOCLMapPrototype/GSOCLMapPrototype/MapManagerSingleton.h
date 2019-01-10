#pragma once
#include "Map_Node.h"
class MapManagerSingleton
{
private:
	static MapManagerSingleton* instance;
	Map_Node** map;
	int next_id;
	MapManagerSingleton();
	~MapManagerSingleton();
public: 
	static MapManagerSingleton* Get_Instance();
	bool Create_Connection(int index_a, int index_b, double freight_cost_per_lb, double travel_cost);
	bool Create_Connection(Map_Node *a, Map_Node *b, double freight_cost_per_lb = 0, double travel_cost = 0);
	bool Remove_Connection(int index_a, int index_b);
	bool Remove_Connection(Map_Node *a, Map_Node *b);
	Map_Node* Create_Map_Node();
	bool Add_Node(Map_Node *m);
	Map_Node* Get_Node(int index);
	bool Remove_Node(int index);
	void Save_Map();
	void Load_Map();
};

