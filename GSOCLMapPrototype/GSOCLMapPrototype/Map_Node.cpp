#include "Map_Node.h"
#include "json.hpp"
void to_json(nlohmann::json& j, const Map_Node& m)
{
	j = nlohmann::json
	{
		{"name", m.name},
		{"map_id", m.map_id},
		{"connections", m.connections},
		{"surface", m.surface},
		{"terrain", m.terrain},
		{"port_level", m.port_level},
		{"airport_level", m.airport_level},
		{"elevator_level", m.elevator_level},
		{"polity", m.polity},
		{"climate", m.climate},
		{"nuclear", m.nuclear},
		{"chemical", m.chemical},
		{"area", m.area},
		{"oxygen", m.oxygen},
		{"air_quality", m.air_quality},
		{"resource_type", m.resource_type},
		{"resource_amount", m.resource_amount}
	};
}

void from_json(const nlohmann::json& j, Map_Node& m) 
{
	j.at("name").get_to(m.name);
	j.at("map_id").get_to(m.map_id);
	j.at("connections").get_to(m.connections);
	j.at("surface").get_to(m.surface);
	j.at("terrain").get_to(m.terrain);
	j.at("port_level").get_to(m.port_level);
	j.at("airport_level").get_to(m.airport_level);
	j.at("elevator_level").get_to(m.elevator_level);
	j.at("polity").get_to(m.polity);
	j.at("climate").get_to(m.climate);
	j.at("nuclear").get_to(m.nuclear);
	j.at("chemical").get_to(m.chemical);
	j.at("area").get_to(m.area);
	j.at("oxygen").get_to(m.oxygen);
	j.at("air_quality").get_to(m.air_quality);
	j.at("resource_type").get_to(m.resource_type);
	j.at("resource_amount").get_to(m.resource_amount);

}
