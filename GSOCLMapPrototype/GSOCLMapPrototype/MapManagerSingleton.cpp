#include "pch.h"
#include "MapManagerSingleton.h"
#include "json.hpp"
#include <vector>
#include <iostream>
#include <fstream>

MapManagerSingleton *MapManagerSingleton::instance;

bool MapManagerSingleton::Check_Flag(Map_Node *m, unsigned char f)
{
	if ((f & m->flags) > 0)
	{
		return true;
	}
	return false;
}

MapManagerSingleton::MapManagerSingleton()
{
	config = ConfigurationSingleton::Get_Instance();
	this->map = new Map_Node*[config->MAX_NUMBER_OF_NODES];
	for (int i = 0; i < config->MAX_NUMBER_OF_NODES; i++)
	{
		map[i] = nullptr;
	}
	this->next_id = -1;
}

MapManagerSingleton::~MapManagerSingleton()
{
	for (int i = 0; i < config->MAX_NUMBER_OF_NODES; i++)
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

Map_Node* MapManagerSingleton::Create_Map_Node()
{
	// If no empty slots exist, just make a new one as before
	if (next_id < 0)
	{
		return new Map_Node();
	}
	Map_Node* node;
	node = new Map_Node(this->next_id);
	this->next_id = this->map[next_id]->Get_Terrain();
	delete(this->map[node->Get_ID()]);
	return node;
}

bool MapManagerSingleton::Add_Node(Map_Node *m)
{
	if (m->Get_ID() >= MAX_NUMBER_OF_NODES)
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
	node->DeleteMapNode(this->next_id);
	this->next_id = id;
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
	std::ifstream save_file("map_save.json");
	nlohmann::json save = nlohmann::json::parse(save_file);
	// Clear all existing nodes
	for (int i = 0; i < Map_Node::Get_Number_Of_Nodes(); i++)
	{
		if (this->map[i] == nullptr)
		{
			continue;
		}
		delete(this->map[i]);
		this->map[i] = nullptr; // this might be totally redundant
	}
	// Get number of nodes -- because of the way this is written to file, it counts empty slots
	int num_nodes = save["Number_Of_Nodes"];
	// Load "Node_list" as vector of json
	nlohmann::json node_list = save["Node_List"].get<std::vector<nlohmann::json>>();
	for (int i = 0; i < num_nodes; i++)
	{

	}
}

