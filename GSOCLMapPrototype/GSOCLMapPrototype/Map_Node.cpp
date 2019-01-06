#include "pch.h"
#include "Map_Node.h"
int Map_Node::number_of_nodes = 0;

Map_Node::Map_Node()
{
	this->map_id = number_of_nodes;
	this->number_of_connections = 0;
	int capacity_number_of_connections = MAX_NUM_CONNECTIONS;
	this->connections = new Connection[capacity_number_of_connections];
	//this->residents = new Population[capacity_number_of_connections];
	for (int i = 0; i < capacity_number_of_connections; i++)
	{
		connections[i] = Connection();
		connections[i].dest_map_id = -1;
	}
	number_of_nodes++;
}

Map_Node::Map_Node(int id)
{
	this->map_id = id;
	this->number_of_connections = 0;
	int capacity_number_of_connections = MAX_NUM_CONNECTIONS;
	this->connections = new Connection[capacity_number_of_connections];
	//this->residents = new Population[capacity_number_of_connections];
	for (int i = 0; i < capacity_number_of_connections; i++)
	{
		connections[i] = Connection();
		connections[i].dest_map_id = -1;
	}
}

// Since it's a pointer, we should change this back to a regular deconstructor
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
	/*if (residents != nullptr)
	{
		delete(residents);
	}*/
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
	node["port_level"] = this->port_level;
	node["airport_level"] = this->airport_level;
	node["elevator_level"] = this->elevator_level;
	node["polity"] = this->polity;
	node["climate"] = this->climate;
	node["nuclear_contamination"] = this->nuclear_contamination;
	node["chemical_contamination"] = this->chemical_contamination;
	node["area"] = this->area;
	node["terrain"] = this->terrain;
	node["atmosphere"] = this->atmosphere;
	node["air_quality"] = this->air_quality;
	node["resource_type"] = this->resource_type;
	node["resource_amount"] = this->resource_amount;
	node["number_of_connections"] = this->number_of_connections;
	node["map_id"] = this->map_id;
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
	/*std::vector<nlohmann::json> populations;
	for (int i = 0; i < this->number_of_residents; i++)
	{
		// Order doesn't matter, so skip empty elements
		if (&this->residents[i] == nullptr)
			continue;
		populations.push_back(Population_To_JSON(this->residents[i]));
	}
	node["residents"] = populations;*/
	return node;
}

Map_Node* Map_Node::From_JSON(nlohmann::json n)
{
	int m_id = n["map_id"];
	int delta = m_id - Map_Node::Get_Number_Of_Nodes();
	Map_Node::Increment_Count(m_id);
	Map_Node* node = new Map_Node();
	//node->Set_Port_Level(n[""])
	//node->Set_Area(n["area"]);
	//node->Set_
	return new Map_Node();
}

nlohmann::json Map_Node::Connection_To_JSON(Connection c)
{
	nlohmann::json conn;
	conn["dest_map_id"] = c.dest_map_id;
	conn["travel_cost"] = c.travel_cost;
	conn["freight_cost"] = c.freight_cost_per_lb;
	return conn;
}

bool Map_Node::Check_Flag(unsigned char f)
{
	if ((f & this->flags) > 0)
	{
		return true;
	}
	return false;
}

void Map_Node::Set_Flag(unsigned char f)
{
	this->flags = f | this->flags;
}

void Map_Node::Toggle_Flag(unsigned char f)
{
	this->flags = f ^ this->flags;
}

void Map_Node::Set_Port_Level(unsigned char p)
{
	this->port_level = p;
}

void Map_Node::Set_Airport_Level(unsigned char a)
{
	this->airport_level = a;
}

void Map_Node::Set_Elevator_Level(unsigned char e)
{
	this->elevator_level = e;
}

void Map_Node::Set_Climate(unsigned char c)
{
	this->climate = c;
}

void Map_Node::Set_Nuclear_Contamination(float n)
{
	this->nuclear_contamination = n;
}

void Map_Node::Set_Chemical_Contamination(float c)
{
	this->chemical_contamination = c;
}

void Map_Node::Set_Area(int a)
{
	this->area = a;
}

void Map_Node::Set_Terrain(int t)
{
	this->terrain = t;
}

void Map_Node::Set_Atmosphere(int a)
{
	this->atmosphere = a;
}

void Map_Node::Set_Air_Quality(int q)
{
	this->air_quality = q;
}

void Map_Node::Set_Resource_Type(int r)
{
	this->resource_type = r;
}

void Map_Node::Set_Resource_Amount(int a)
{
	this->resource_amount = a;
}

unsigned char Map_Node::Get_Port_Level()
{
	return this->port_level;
}

unsigned char Map_Node::Get_Airport_Level()
{
	return this->airport_level;
}

unsigned char Map_Node::Get_Elevator_Level()
{
	return this->elevator_level;
}

unsigned char Map_Node::Get_Climate()
{
	return this->climate;
}

float Map_Node::Get_Nuclear_Contamination()
{
	return this->nuclear_contamination;
}

float Map_Node::Get_Chemical_Contamination()
{
	return this->chemical_contamination;
}

int Map_Node::Get_Area()
{
	return this->area;
}

int Map_Node::Get_Terrain()
{
	return this->terrain;
}

int Map_Node::Get_Atmosphere()
{
	return this->atmosphere;
}

int Map_Node::Get_Air_Quality()
{
	return this->air_quality;
}

int Map_Node::Get_Resource_Type()
{
	return this->resource_type;
}

int Map_Node::Get_Resource_Amount()
{
	return this->resource_amount;
}
