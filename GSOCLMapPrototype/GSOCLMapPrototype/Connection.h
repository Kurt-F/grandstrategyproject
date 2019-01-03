#pragma once
#include "Map_Node.h"
struct Connection
{
	int dest_map_id;
	float travel_cost;
	float freight_cost_per_lb;
};