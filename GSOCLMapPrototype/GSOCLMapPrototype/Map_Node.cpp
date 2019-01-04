#include "pch.h"
#include "Map_Node.h"
int Map_Node::number_of_nodes = 0;

Map_Node::Map_Node()
{
	this->map_id = number_of_nodes;
	this->number_of_connections = 0;
	int capacity_number_of_connections = MAX_NUM_CONNECTIONS;
	this->connections = new Connection[capacity_number_of_connections];
	this->residents = new Population[capacity_number_of_connections];
	for (int i = 0; i < capacity_number_of_connections; i++)
	{
		connections[i] = Connection();
		connections[i].dest_map_id = -1;
	}
	number_of_nodes++;
}


bool Map_Node::DeleteMapNode()
{
	if (this->map_id == -1)
	{
		return false; // All deleted map_ids are -1
	}
	if (connections != nullptr)
	{
		delete(connections);
	}
	if (residents != nullptr)
	{
		delete(residents);
	}
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
	int max_num_connections = MAX_NUM_CONNECTIONS;
	if (this->number_of_connections >= max_num_connections || Has_Connection_Index(c.dest_map_id))
	{
		return false;
	}
	this->connections[number_of_connections] = c;
	number_of_connections++;
	return true;
}

bool Map_Node::Has_Connection_Index(int index)
{
	int connection_num = 0;
	Connection c = this->connections[connection_num];
	while (connection_num < this->number_of_connections)
	{
		c = this->connections[connection_num];
		if (c.dest_map_id ==index)
		{
			return true;
		}
		connection_num++;
	}
	return false;
}

bool Map_Node::Has_Connection(Map_Node m)
{
	Connection c = this->connections[0];
	int number_of_connections = this->number_of_connections;
	int connection_num = 0;
	while(connection_num < number_of_connections)
	{
		c = this->connections[connection_num];
		if (c.dest_map_id == m.Get_ID())
		{
			return true;
		}
		connection_num++;
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
			index = i; 
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
		return true;
	}
}

int Map_Node::Get_Number_Of_Nodes()
{
	return number_of_nodes;
}

/* Methods for saving map to file */
nlohmann::json Map_Node::To_JSON()
{
	nlohmann::json node;
	node["map_id"] = this->map_id;
	node["area"] = this->area;
	node["terrain"] = this->terrain;
	node["number_of_connections"] = this->number_of_connections;
	// Create vector of connections
	std::vector<nlohmann::json> conns;
	for (int i = 0; i < this->number_of_connections; i++)
	{
		if (&this->connections[i] == nullptr)
			continue;
		conns.push_back(Connection_To_JSON(this->connections[i]));
	}
	node["connections"] = conns;
	// Create vector of populations
	std::vector<nlohmann::json> populations;
	for (int i = 0; i < this->number_of_residents; i++)
	{
		// Order doesn't matter, so skip empty elements
		if (&this->residents[i] == nullptr)
			continue;
		populations.push_back(Population_To_JSON(this->residents[i]));
	}
	node["residents"] = populations;
	return node;
}

nlohmann::json Map_Node::Connection_To_JSON(Connection c)
{
	nlohmann::json conn;
	conn["dest_map_id"] = c.dest_map_id;
	conn["travel_cost"] = c.travel_cost;
	conn["freight_cost"] = c.freight_cost_per_lb;
	return conn;
}

nlohmann::json Map_Node::Population_To_JSON(Population c)
{	
	nlohmann::json pop;
	pop["size"] = c.size;
	pop["flags"] = c.flags;
	pop["culture"] = c.culture;
	pop["profession"] = c.profession;
	pop["religion"] = c.religion;
	pop["ideology"] = c.ideology;
	pop["birth_rate"] = c.birth_rate;
	// Create sub-object of needs
	nlohmann::json needs;
	for (int i = 0; i < NUM_GOODS; i++)
	{
		needs[i] = c.needs[i]; // Uses indices as json keys, might be a bad idea. 
							   // Ideally can just use "ECON_*" constants to decode.
							   // No null checking to preserve structure
	}
	pop["needs"] = needs;
	return pop;
}