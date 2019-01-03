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

bool MapManagerSingleton::Create_Connection(Map_Node a, Map_Node b)
{
	// create connection from a to b
	// create connection from b to a
	// add connection 1 to a
	// add connection 2 to b 
	return false;
}

bool MapManagerSingleton::Add_Node(Map_Node m)
{
	if(this->number_of_nodes == MAX_NUMBER_OF_NODES)
		return false;
	this->number_of_nodes++;
	return true;
}
