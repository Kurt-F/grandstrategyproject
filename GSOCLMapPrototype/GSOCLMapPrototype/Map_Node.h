#pragma once
#include "Connection.h"
#include <string>
// Constants for defining each element in modifier array
// Struct version of Map_Node
struct Map_Node
{
	std::string name;
	int map_id;
	unsigned char surface_type;
};