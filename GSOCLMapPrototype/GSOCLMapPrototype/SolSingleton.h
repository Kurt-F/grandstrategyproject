#pragma once
#include "json.hpp"
#include <iostream>
#include "MapManagerSingleton.h"
#include <map>
#include <string>
class GSOLSingleton
{
private:
	static GSOLSingleton *instance;
	std::map<std::string, MapManager&> solar_system;
	GSOLSingleton()
	{
	}
public: 
	GSOLSingleton* Get_Instance()
	{
		if (instance == nullptr)
		{
			instance = new	GSOLSingleton();
		}
		return instance;
	}

	void SetPlanet(std::string name, MapManager &manager)
	{
		solar_system[name] = manager;
	}

	MapManager& GetPlanet(std::string name)
	{
		if (solar_system.find(name) != solar_system.end())
		{
			std::cerr << "Planet does not exist\n";
			std::exit(1);
		}
		return solar_system[name];
	}
};