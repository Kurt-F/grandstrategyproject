#include "pch.h"
#include "Tests.h"
#include "MapManagerSingleton.h"
#include "Map_Node.h"
#include "ConfigurationSingleton.h"
int main()
{
	ConfigurationSingleton* config_test = ConfigurationSingleton::Get_Instance();
	Tests::Run_All_Tests(true);
	// Create a map with two map nodes
	MapManagerSingleton* manager = MapManagerSingleton::Get_Instance();
	//manager->Remove_Node(0);
	/*Map_Node* n_1 = manager->Create_Map_Node();
	Map_Node* n_2 = manager->Create_Map_Node();
	manager->Add_Node(n_1);
	manager->Add_Node(n_2);
	manager->Create_Connection(n_1, n_2, 12, 10);
	// Save map to file*/
	//manager->Save_Map();
	return 0;
	
}