#include "pch.h"
#include "Map_Node.h"


Map_Node::Map_Node()
{
	this->map_id = number_of_nodes;
	number_of_nodes++;
}


Map_Node::~Map_Node()
{
	number_of_nodes--; // Maybe?
}

int Map_Node::Get_ID()
{
	return 0;
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
