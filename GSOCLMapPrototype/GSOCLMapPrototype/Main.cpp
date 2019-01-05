#include "pch.h"
#include "Tests.h"
#include "MapManagerSingleton.h"
#include "Map_Node.h"

int main()
{
	//Tests::Run_All_Tests(true);
	// Create a map with two map nodes
	MapManagerSingleton* manager = MapManagerSingleton::Get_Instance();
	Map_Node* n_1 = new Map_Node();
	Map_Node* n_2 = new Map_Node();
	manager->Add_Node(n_1);
	manager->Add_Node(n_2);
	manager->Create_Connection(n_1, n_2, 12, 10);
	// Save map to file
	manager->Save_Map();
	return 0;
}