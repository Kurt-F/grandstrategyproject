#pragma once
#include "Map_Node.h"
#include "json.hpp"
#include "Connection.h"

struct Connection
{
	int dest_node;
	float travel_cost;
	float freight_cost_per_lb;
};