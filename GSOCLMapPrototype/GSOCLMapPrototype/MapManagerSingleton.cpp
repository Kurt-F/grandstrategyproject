#include "pch.h"
#include "MapManagerSingleton.h"
#include "json.hpp"
#include <vector>
#include <iostream>
#include <fstream>

MapManagerSingleton *MapManagerSingleton::instance;

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
	if (index_a >= 0 && index_a < this->number_of_nodes && index_b >= 0 && index_b < this->number_of_nodes)
	{
		if (map[index_a]->map_id == index_a && map[index_b]->map_id == index_b)
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
	a_to_b.dest_node = b->map_id;
	a_to_b.freight_cost_per_lb = freight_cost_per_lb; 
	a_to_b.travel_cost = travel_cost;
	Connection b_to_a = Connection();
	b_to_a.dest_node = a->map_id;
	b_to_a.freight_cost_per_lb = freight_cost_per_lb;
	b_to_a.travel_cost = travel_cost;
	a->connections.push_back(a_to_b);
	b->connections.push_back(b_to_a);
	// Check if the connections are set up correctly. Pointer values should be same. 
	if (a->connections.at(a->connections.size()).dest_node != b->map_id)
		return false;
	if (b->connections.at(b->connections.size()).dest_node != a->map_id)
		return false;
	return true;
}


bool MapManagerSingleton::Remove_Connection(int index_a, int index_b)
{
	if (index_a >= 0 && index_a < this->number_of_nodes && index_b >= 0 && index_b < this->number_of_nodes)
	{
		if (map[index_a]->map_id == index_a && map[index_b]->map_id == index_b)
		{
		return 	Remove_Connection(map[index_a], map[index_b]);
		}
	}
	return false;
}

bool MapManagerSingleton::Remove_Connection(Map_Node *a, Map_Node *b)
{
	if (!Node_Has_Connection(a, b) || !Node_Has_Connection(b, a))
	{
		return false;
	}
	else
	{
		for (int i = 0; i < a->connections.size(); i++)\
		{
			if (a->connections.at(i).dest_node == a->map_id) 
			{
				delete(&a->connections.at(i));
				return true;
			}
		}
	}
	// Return false if the connection does not exist
	return false;
}

Map_Node* MapManagerSingleton::Create_Map_Node()
{
	// If no empty slots exist, just make a new one as before
	if (next_id < 0)
	{
		return new Map_Node();
	}
	Map_Node* node;
	node->map_id = this->next_id;
	this->next_id = this->map[next_id]->terrain;
	delete(this->map[node->map_id]);
	return node;
}

bool MapManagerSingleton::Add_Node(Map_Node *m)
{
	if (m->map_id >= config->MAX_NUMBER_OF_NODES)
		return false;
	this->map[m->map_id] = m;
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
	for (int i = 0; i < node->connections.size(); i++)
	{
		Delete_Connection(map[node->connections.at(i).dest_node], map[id]);
		delete(&map[id]->connections[i]); //This might not work
	}
	// "Free up" space in the array, use terrain to point to next free slot
	map[next_id]->terrain = id;
	next_id = id;
	map[id]->map_id = -1;
	map[id]->terrain = -1;
	// TODO: Send "message" to anything living on the node that it's gone
	return true;
}

bool MapManagerSingleton::Node_Has_Connection(Map_Node* a, Map_Node* b)
{
	for (int i = 0; i < (int) a->connections.size(); i++)
	{
		if (a->connections[i].dest_node == b->map_id)
			return true;
	}
	return false;
}

bool MapManagerSingleton::Delete_Connection(Map_Node* a, Map_Node* b)
{
	// Transfer all connections to a new vector other than the deleted ones
	bool deleted = false;
	int offset = 0;
	std::vector<Connection> updated;
	for (int i = 0; i < a->connections.size(); i++)
	{
		if (a->connections[i].dest_node == b->map_id)
		{
			offset++;
			deleted = true;
			continue;
		}
		updated.push_back(a->connections[i + offset]);
	}
	if (!deleted)
		return false;
	std::vector<Connection> temp;
	temp = a->connections;
	a->connections = updated;
	delete(&temp);
	return true;
}
struct test
{
	int i; 
	int b;
};
// Save the entire map to file
void MapManagerSingleton::Save_Map()
{
	std::vector<nlohmann::json> nodes;
	for (int i = 0; i < number_of_nodes; i++) 
	{
		if (&this->map[i] == nullptr)
		{
			continue;
		}
		// If the node exists, convert to json and add it to the vector
		nodes.push_back(Node_To_Json(*this->map[i]));
	}
	nlohmann::json map;
	// Note: Saving to file from here is probably temporary 
	map["Number_Of_Nodes"] =  number_of_nodes;
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
	for (int i = 0; i < number_of_nodes; i++)
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



// JSON serialization 
nlohmann::json MapManagerSingleton::Conn_To_Json(Connection c)
{
	return nlohmann::json
	{
		{"dest_node", c.dest_node},
		{"travel_cost", c.travel_cost},
		{"freight_cost", c.freight_cost_per_lb}
	};
}
Connection MapManagerSingleton::Conn_From_Json(nlohmann::json c)
{
	Connection conn;
	conn.dest_node = c["dest_node"];
	conn.travel_cost = c["travel_cost"];
	conn.freight_cost_per_lb = c["freight_cost"];
	return conn;
}

nlohmann::json MapManagerSingleton::Node_To_Json(Map_Node m)
{
	std::vector<nlohmann::json> conns;
	for (int i = 0; i < m.connections.size(); i++)
	{
		conns.push_back(Conn_To_Json(m.connections.at(i)));
	}
	return nlohmann::json
	{
		{"name", m.name},
		{"map_id", m.map_id},
		{"connections", conns}, 
		{"surface", m.surface},
		{"terrain", m.terrain},
		{"port_level", m.port_level},
		{"airport_level", m.airport_level},
		{"elevator_level", m.elevator_level},
		{"polity", m.polity},
		{"climate", m.climate},
		{"nuclear", m.nuclear},
		{"chemical", m.chemical},
		{"area", m.area},
		{"oxygen", m.oxygen},
		{"air_quality", m.air_quality},
		{"resource_type", m.resource_type},
		{"resource_amount", m.resource_amount}
	};
}

void MapManagerSingleton::Node_From_Json(const nlohmann::json& j, Map_Node& m)
{
	j.at("name").get_to(m.name);
	j.at("map_id").get_to(m.map_id);
	//j.at("connections").get_to(m.connections); Add manual conversion
	j.at("surface").get_to(m.surface);
	j.at("terrain").get_to(m.terrain);
	j.at("port_level").get_to(m.port_level);
	j.at("airport_level").get_to(m.airport_level);
	j.at("elevator_level").get_to(m.elevator_level);
	j.at("polity").get_to(m.polity);
	j.at("climate").get_to(m.climate);
	j.at("nuclear").get_to(m.nuclear);
	j.at("chemical").get_to(m.chemical);
	j.at("area").get_to(m.area);
	j.at("oxygen").get_to(m.oxygen);
	j.at("air_quality").get_to(m.air_quality);
	j.at("resource_type").get_to(m.resource_type);
	j.at("resource_amount").get_to(m.resource_amount);
}