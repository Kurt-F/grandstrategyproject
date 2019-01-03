#pragma once
#include "Population.h"	
// Terrain constants
#define FOOTHILS 0
#define DESERT 1
#define DECIDUOUS 2
// TODO: add better terrain
struct Connection
{
	int test;
	Map_Node n;
	float travel_cost;
	float freight_cost_per_lb;
};
class Map_Node
{
private:
	unsigned char terrain;
	Connection* connections;
	Population* residents;
public:
	Map_Node();
	~Map_Node();
};

