#pragma once
#include "Pop.h"

// Connection struct. 
// Connections model a type of connection between provinces: Highways, rail, plane, etc.
struct Connection 
{
	MapNode	destination; // Two connection structs per bidirectional connection. 
	float travel_cost;
	float freight_cost;
};
class MapNode
{
private: 
	int* resources;
	Pop* residents;
	Connection* connections;
public:
	MapNode();
	~MapNode();
};

