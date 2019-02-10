#pragma once
#include "json.hpp"

class ConfigurationSingleton
{
private:
	static ConfigurationSingleton* instance;
	ConfigurationSingleton(nlohmann::json c);
	ConfigurationSingleton();
	~ConfigurationSingleton();
public:
	static ConfigurationSingleton* Get_Instance();
	/* Global constants */
	// Map_Node constants
	const int MAX_NUM_CONNECTIONS;
	const int MAX_NUMBER_OF_NODES;
};

