#pragma once
#include "Map_Node.h"
#include "ConfigurationSingleton.h"
#include "json.hpp"
class MapManagerSingleton
{
private:
	// BEGIN node transfer
	static int number_of_nodes;
	bool Check_Flag(Map_Node *m, unsigned char f); // Returns true if the given flag f is set
	void Set_Flag(unsigned char f); // Sets the given flag to true
	void Toggle_Flag(unsigned char f); // Inverts the state of the given flag
	// END node transfer
	ConfigurationSingleton* config;
	static MapManagerSingleton* instance;
	Map_Node** map;
	int next_id;
	// Check if node a has a connection to node b
	bool Node_Has_Connection(Map_Node* a, Map_Node* b);
	// Deletes all conbnections from node a to node b, returns false if not found
	bool Delete_All_Connections(Map_Node* a, Map_Node* b);
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

