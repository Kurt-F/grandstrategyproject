#pragma once
#include "Map_Node.h"
#include "ConfigurationSingleton.h"
#include "json.hpp"
class MapManagerSingleton
{
private:
	static MapManagerSingleton* instance;
	ConfigurationSingleton* config;
	int number_of_nodes;
	Map_Node** map;
	int next_id;
	// Serialization functions
	nlohmann::json Conn_To_Json(Connection c);
	Connection Conn_From_Json(nlohmann::json c);
	nlohmann::json Node_To_Json(Map_Node m);
	void Node_From_Json(const nlohmann::json& j, Map_Node& m);
	// Check if node a has a connection to node b
	// Deletes ALL connections from node a to node b, returns false if not found
	bool Delete_Connection(Map_Node* a, Map_Node* b);
	bool Delete_Map_Node(Map_Node* m);
	MapManagerSingleton();
	~MapManagerSingleton();
public: 
	static MapManagerSingleton* Get_Instance();
	bool Create_Connection(int index_a, int index_b, double freight_cost_per_lb, double travel_cost);
	bool Create_Connection(Map_Node *a, Map_Node *b, double freight_cost_per_lb = 0, double travel_cost = 0);
	bool Remove_Connection(int index_a, int index_b);
	bool Remove_Connection(Map_Node *a, Map_Node *b);
	bool Node_Has_Connection(Map_Node* a, Map_Node* b);
	Map_Node* Create_Map_Node();
	bool Add_Node(Map_Node *m);
	Map_Node* Get_Node(int index);
	bool Remove_Node(int index);
	void Save_Map();
	void Load_Map();
};

