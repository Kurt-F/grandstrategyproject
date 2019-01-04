#include "pch.h"
#include "MapManagerSingleton.h"

MapManagerSingleton *MapManagerSingleton::instance;

MapManagerSingleton::MapManagerSingleton()
{
	this->map = new Map_Node[MAX_NUMBER_OF_NODES];
	this->number_of_nodes = 0;
	instance = this; 
}

MapManagerSingleton::~MapManagerSingleton()
{
	delete(this->map); // I doubt the game will ever run without this object but who knows
}

MapManagerSingleton MapManagerSingleton::Get_Instance()
{
	if (instance == nullptr)
	{
		instance = new MapManagerSingleton();
	}
	return *instance;
}

bool MapManagerSingleton::Create_Connection(Map_Node &a, Map_Node &b, int freight_cost_per_lb, int travel_cost)
{
	// create connection from a to b
	Connection a_to_b = Connection();
	a_to_b.dest_map_id = b.Get_ID(); 
	a_to_b.freight_cost_per_lb = freight_cost_per_lb; 
	a_to_b.travel_cost = travel_cost;
	Connection b_to_a = Connection();
	b_to_a.dest_map_id = a.Get_ID();
	b_to_a.freight_cost_per_lb = freight_cost_per_lb;
	b_to_a.travel_cost = travel_cost;
	return (a.Add_Connection(a_to_b) && b.Add_Connection(b_to_a));
}

bool MapManagerSingleton::Remove_Connection(Map_Node &a, Map_Node &b)
{
	if (!a.Has_Connection(b) || (!b.Has_Connection(a)))
	{
		return false;
	}
	else
	{
		if (a.Delete_Connection(b.Get_ID()) && b.Delete_Connection(a.Get_ID()))
		{
			return true;
		}
		else
		{
			return false; 
		}
	}
}

bool MapManagerSingleton::Add_Node(Map_Node m)
{
	if(m.Get_ID() >= MAX_NUMBER_OF_NODES)
		return false;
		this->map[m.Get_ID()] = m;
	return true;
}

bool MapManagerSingleton::Remove_Node(int id)
{
	// Remove all connections going in and out of this node
	Map_Node* node = &map[id];
	int total_connections = node->Get_Number_Of_Connections();
	for (int i = 0; i < total_connections; i++)
	{
		map[node->Get_ID_Of_Connection(i)].Delete_Connection(id);
	}
	while (node->Get_Number_Of_Connections() != 0)
	{
		node->Delete_Connection(0);
	}
	node->DeleteMapNode();
	return true;
}