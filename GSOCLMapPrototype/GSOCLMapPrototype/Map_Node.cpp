#include "pch.h"
#include "Map_Node.h"

int Map_Node::number_of_nodes;

Map_Node::Map_Node()
{
	this->map_id = number_of_nodes;
	number_of_nodes++;
}


bool Map_Node::DeleteMapNode()
{
	if (this->map_id == -1)
	{
		return false; // All deleted map_ids are -1
	}
	delete(connections);
	delete(residents);
	this->map_id = -1;
	this->number_of_connections = 0;
	this->terrain = 0;
	return true;
}

int Map_Node::Get_ID()
{
	return this->map_id;
}

int Map_Node::Get_Number_Of_Connections()
{
	return this->number_of_connections;
}

int Map_Node::Get_ID_Of_Connection(int index)
{
	return this->connections[index].dest_map_id;
}

// Returns false if max connections already reached. Actually creating connections is left to the manager
bool Map_Node::Add_Connection(Connection c)
{
	if (this->number_of_connections >= MAX_NUM_CONNECTIONS)
	{
		return false;
	}
	this->connections[number_of_connections] = c;
	number_of_connections++;
	return true;
}

bool Map_Node::Has_Connection(Map_Node m)
{
	Connection c = this->connections[0];
	while(&c != nullptr)
	{
		if (c.dest_map_id == m.Get_ID())
		{
			return true;
		}
	}
	return false;
}

bool Map_Node::Delete_Connection(int id)
{
	int index = -1;
	for (int i = 0; i < this->number_of_connections; i++)
	{
		if (this->connections[i].dest_map_id == id)
		{
			index = id; 
			break; 
		}
	}
	if (index == -1)
	{
		return false; 
	}
	else
	{
		this->connections[index] = this->connections[this->number_of_connections - 1];
		this->number_of_connections--;
	}
}