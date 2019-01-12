#include "pch.h"
#include "ConfigurationSingleton.h"
#include "json.hpp"

ConfigurationSingleton::ConfigurationSingleton(int num_nodes, int num_conns) : 
	MAX_NUMBER_OF_NODES(num_nodes), 
	MAX_NUM_CONNECTIONS(num_conns)
{

}


ConfigurationSingleton::~ConfigurationSingleton()
{
}

ConfigurationSingleton* ConfigurationSingleton::Get_Instance()
{
	if (instance == nullptr)
	{
		// Extract constants and pass to constructor
		nlohmann::json config_file;
		instance = new ConfigurationSingleton();
	}
	return instance;
}
