#pragma once
class MapManagerSingleton
{
private:
	MapManagerSingleton();
	~MapManagerSingleton();
public:
	MapManagerSingleton Get_Instance();
};

