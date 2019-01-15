#pragma once
#include "json.hpp"
struct Connection
{
	int dest_node;
	float travel_cost;
	float freight_cost_per_lb;
};