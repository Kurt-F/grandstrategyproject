#include "pch.h"
#include "ConfigurationSingleton.h"
#include <fstream>
#include <iostream>
ConfigurationSingleton* ConfigurationSingleton::instance;

ConfigurationSingleton::ConfigurationSingleton(nlohmann::json c) : 
	MAX_NUMBER_OF_NODES(c["MAX_NUMBER_OF_NODES"]), 
	MAX_NUM_CONNECTIONS(c["MAX_NUM_CONNECTIONS"])
{

}


ConfigurationSingleton::~ConfigurationSingleton()
{
}

ConfigurationSingleton* ConfigurationSingleton::Get_Instance()
{
	if (instance == nullptr)
	{
		try
		{
			// Load config data and pass to constructor
			std::ifstream infile("data/config/config.json");
			nlohmann::json config_file = nlohmann::json::parse(infile);
			instance = new ConfigurationSingleton(config_file);
		}
		catch (...)
		{
			std::cout << "Config failed" << std::endl;
		}
	}
	return instance;
}
