#pragma once
#include "Population.h"	
#include "Connection.h"
// Terrain constants
#define FOOTHILLS 0
#define DESERT 1
#define DECIDUOUS 2
// Misc constants
#define MAX_NUM_CONNECTIONS 20
#define MAX_NUMBER_OF_NODES 500000
// TODO: add better terrain

class Map_Node
{
private:
	static int number_of_nodes;
	int map_id;
	unsigned char terrain;
	unsigned char number_of_connections;
	Connection* connections;
	Population* residents;
public:
	Map_Node();
	~Map_Node();
	int Get_ID();
	bool Add_Connection(Connection c);
	bool Has_Connection(Map_Node m);
};

