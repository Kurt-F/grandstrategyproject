#pragma once
#include "Connection.h"
#include "Map_Node.h"
#include "json.hpp"
#include <string>
#include <vector>
// Json serialization functions
void to_json(nlohmann::json& j, const Map_Node& p);
void from_json(const nlohmann::json& j, Map_Node& p);
// Struct version of Map_Node
struct Map_Node
{
	std::string name;
	int map_id;
	std::vector<Connection> connections;
	unsigned char surface;
	unsigned char terrain;
	unsigned char port_level;
	unsigned char airport_level;
	unsigned char elevator_level;
	unsigned char polity; // PLACEHOLDER
	unsigned char climate; // PLACEHOLDER
	float nuclear;
	float chemical;
	int area; // Square miles
	float oxygen; // Oxygen ppm per cubic foot or something
	float air_quality; // Measure of common pollutants
	int resource_type; // PLACEHOLDER
	int resource_amount; // Tons of the resource available
};