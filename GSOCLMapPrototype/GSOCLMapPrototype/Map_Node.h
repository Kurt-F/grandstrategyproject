#pragma once
#include "Population.h"	
#include "Connection.h"
#include "json.hpp"

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
	int area;
	unsigned char terrain;
	unsigned char number_of_connections;
	Connection* connections;
	int number_of_residents; // TODO: Make this a smaller type
	Population* residents;
	nlohmann::json Connection_To_JSON(Connection c);
	nlohmann::json Population_To_JSON(Population c);

public:
	Map_Node();
	// ~Map_Node(); Since all of our Map_Nodes are not dynamic, we will have a delete function that essentially sets it to the Map_Node equal of "NULL"
	bool DeleteMapNode();
	int Get_ID();
	int Get_Number_Of_Connections();
	int Get_ID_Of_Connection(int index);
	bool Add_Connection(Connection c);
	bool Has_Connection_Index(int index);
	bool Has_Connection(Map_Node &m);
	bool Delete_Connection(int id);
	nlohmann::json To_JSON();
};

