#include "pch.h"
#include "MapManagerSingleton.h"
#include "json.hpp"
#include <vector>
#include <iostream>
#include <fstream>

MapManagerSingleton *MapManagerSingleton::instance;

MapManagerSingleton::MapManagerSingleton()
{
	this->map = new Map_Node*[MAX_NUMBER_OF_NODES];
	for (int i = 0; i < MAX_NUMBER_OF_NODES; i++)
	{
		map[i] = nullptr;
	}
}

MapManagerSingleton::~MapManagerSingleton()
{
	for (int i = 0; i < MAX_NUMBER_OF_NODES; i++)
	{
		if (map[i] != nullptr)
		{
			delete(map[i]);
		}
	}
	delete(this->map); // I doubt the game will ever run without this object but who knows
}

MapManagerSingleton* MapManagerSingleton::Get_Instance()
{
	if (instance == nullptr)
	{
		instance = new MapManagerSingleton();
	}
	return instance;
}

bool MapManagerSingleton::Create_Connection(int index_a, int index_b, double freight_cost_per_lb, double travel_cost)
{
	if (index_a >= 0 && index_a < Map_Node::Get_Number_Of_Nodes() && index_b >= 0 && index_b < Map_Node::Get_Number_Of_Nodes())
	{
		if (map[index_a]->Get_ID() == index_a && map[index_b]->Get_ID() == index_b)
		{
		 return	Create_Connection(map[index_a], map[index_b], freight_cost_per_lb, travel_cost);
		}
	}
	return false; 
}

bool MapManagerSingleton::Create_Connection(Map_Node *a, Map_Node *b, double freight_cost_per_lb, double travel_cost)
{
	// create connection from a to b
	Connection a_to_b = Connection();
	a_to_b.dest_map_id = b->Get_ID();
	a_to_b.freight_cost_per_lb = freight_cost_per_lb; 
	a_to_b.travel_cost = travel_cost;
	Connection b_to_a = Connection();
	b_to_a.dest_map_id = a->Get_ID();
	b_to_a.freight_cost_per_lb = freight_cost_per_lb;
	b_to_a.travel_cost = travel_cost;
	return (a->Add_Connection(a_to_b) && b->Add_Connection(b_to_a));
}

bool MapManagerSingleton::Remove_Connection(int index_a, int index_b)
{
	if (index_a >= 0 && index_a < Map_Node::Get_Number_Of_Nodes() && index_b >= 0 && index_b < Map_Node::Get_Number_Of_Nodes())
	{
		if (map[index_a]->Get_ID() == index_a && map[index_b]->Get_ID() == index_b)
		{
		return 	Remove_Connection(map[index_a], map[index_b]);
		}
	}
	return false;
}

bool MapManagerSingleton::Remove_Connection(Map_Node *a, Map_Node *b)
{
	if (!a->Has_Connection(*b) || (!b->Has_Connection(*a)))
	{
		return false;
	}
	else
	{
		if (a->Delete_Connection(b->Get_ID()) && b->Delete_Connection(a->Get_ID()))
		{
			return true;
		}
		else
		{
			return false; 
		}
	}
}

bool MapManagerSingleton::Add_Node(Map_Node *m)
{
	if(m->Get_ID() >= MAX_NUMBER_OF_NODES)
		return false;
	this->map[m->Get_ID()] = m;
	return true;
}

Map_Node* MapManagerSingleton::Get_Node(int id)
{
	return (map[id]);
}

bool MapManagerSingleton::Remove_Node(int id)
{
	// Remove all connections going in and out of this node
	Map_Node* node = map[id];
	int total_connections = node->Get_Number_Of_Connections();
	for (int i = 0; i < total_connections; i++)
	{
		map[node->Get_ID_Of_Connection(i)]->Delete_Connection(id);
	}
	while (node->Get_Number_Of_Connections() != 0)
	{
		node->Delete_Connection(0);
	}
	node->DeleteMapNode();
	// TODO: Send "message" to anything living on the node that it's gone
	return true;
}

// Save the entire map to file
void MapManagerSingleton::Save_Map()
{
	// Create vector of map nodes
	std::vector<nlohmann::json> nodes = {};
	for (int i = 0; i < Map_Node::Get_Number_Of_Nodes(); i++) 
	{
		if (&this->map[i] == nullptr)
		{
			continue;
		}
		// If the node exists, add it to the vector
		nodes.push_back(this->map[i]->To_JSON());
	}
	nlohmann::json map;
	// Note: Saving to file from here is probably temporary 
	map["Number_Of_Nodes"] = Map_Node::Get_Number_Of_Nodes();
	map["Node_List"] = nodes;
	std::ofstream save_file;
	save_file.open("map_save.json");
	save_file << map.dump(); // Translate JSON to a string then dump to file
	save_file.close();
}

// Load an entire map from file. Overwrites existing provinces
void MapManagerSingleton::Load_Map()
{
	// Open file, read in entire file buffer as json::parse(file);
	std::ifstream save_file;
	save_file.open("map_save.json");
	std::string raw;
	std::string line;
	while (std::getline(save_file, line))
	{
		raw += line;
	}
	nlohmann::json save = nlohmann::json::parse(raw);
	// Get number of nodes -- because of the way this is written to file, it counts empty slots
	int num_nodes = save["Number_Of_Nodes"];
	// Load "Node_list" as vector of json
	nlohmann::json node_list = save["Node_List"];
	for (int i = 0; i < num_nodes; i++)
	{
		// Get map_id
		int m_id = node_list
		// while(map_id > current_node_count or whatever)
			// increment
		// Create node

		// etc
		// Get connections of node
		// for each connection
			// node->connections[etc] = etc
		// If node exists at map_id, delete it
		// this->map[map_id] = node
	}
}

