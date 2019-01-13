#pragma once
#include "Map_Node.h"
struct Connection
{
	Map_Node* dest_node;
	float travel_cost;
	float freight_cost_per_lb;
};