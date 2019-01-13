#pragma once
#include "Map_Node.h"
#include "json.hpp"
#include "Connection.h"

// Json serialization functions
void to_json(nlohmann::json& j, const Connection& c);
void from_json(const nlohmann::json& j, Connection& c);

struct Connection
{
	int dest_node;
	float travel_cost;
	float freight_cost_per_lb;
};