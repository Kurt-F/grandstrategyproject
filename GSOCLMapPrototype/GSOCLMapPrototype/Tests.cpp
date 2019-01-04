#include "pch.h"
#include "Tests.h"
#include "MapManagerSingleton.h"
void Tests::Print_Test_Results(bool pass_fail, std::string name_of_message, std::string message)
{
	if (pass_fail)
	{
		std::cout << "The test " << name_of_message.c_str() << " passed with a return message of " << message.c_str() << std::endl;
	}

	else
	{
		std::cout << "The test " << name_of_message.c_str() << " failed with a return message of " << message.c_str() << std::endl;
	}
}

bool Tests::Run_All_Tests(bool recursive_print_results)
{
	bool passed = true; 
	passed = passed && Run_Map_Tests(recursive_print_results, recursive_print_results);
	return passed;
}

bool Tests::Run_Map_Tests(bool print_results, bool recursive_print_results)
{
	bool map_tests = true;
	map_tests = Create_MapManagerSingleton(recursive_print_results) && map_tests;
	map_tests = Add_Nodes(recursive_print_results) && map_tests;
	map_tests = Create_Connections(recursive_print_results) && map_tests;
	if (print_results)
	{
		if (map_tests)
		{
			Print_Test_Results(map_tests, "map tests", "they worked");
		}
		else
		{
			Print_Test_Results(map_tests, "map tests", "did not work");
		}
	}
	return map_tests;
}

bool Tests::Create_MapManagerSingleton(bool print_results)
{
	try
	{
		MapManagerSingleton *i = MapManagerSingleton::Get_Instance();
		MapManagerSingleton *j = MapManagerSingleton::Get_Instance();
		if (print_results)
		{
			Print_Test_Results(true, "Create Map Manager", "it works");
		}
		return true;
	}
	catch (...)
	{
		if (print_results)
		{
			Print_Test_Results(false, "Create Map Manager", "it does not work");
		}
		return false; 
	}
}

bool Tests::Add_Nodes(bool print_results)
{
	MapManagerSingleton *manager = MapManagerSingleton::Get_Instance();
	for (int i = 0; i < 10; i++)
	{
		Map_Node mp;
		mp = Map_Node();
		manager->Add_Node(mp);
	}
	for (int i = 0; i < 10; i++)
	{
		if (manager->Get_Node(i).Get_ID() != i)
		{
			Print_Test_Results(false, "Add Nodes", "nodes added incorrectly");
			return false;
		}
	}
	Print_Test_Results(true, "Add Nodes", "nodes added correctly");
	return true;
}

bool Tests::Create_Connections(bool print_results)
{
	MapManagerSingleton *manager = MapManagerSingleton::Get_Instance();
	Map_Node a = manager->Get_Node(0);
	Map_Node b = manager->Get_Node(1);
	Map_Node c = manager->Get_Node(2);
	manager->Create_Connection(a, b, 30, 25);
	manager->Create_Connection(a, c, 15, 20);
	bool it_works = true;
	if (!manager->Get_Node(0).Has_Connection(manager->Get_Node(1)))
	{
		it_works = false;
	}
	if (!manager->Get_Node(0).Has_Connection(manager->Get_Node(2)))
	{
		it_works = false;
	}
	if(manager->Get_Node(1).Has_Connection(manager->Get_Node(2)))
	{
		it_works = false;
	}
	if (it_works)
	{
		Print_Test_Results(it_works, "Creating Connections", "it worked");
	}
	else
	{
		Print_Test_Results(it_works, "Creating Connections", "it did not work");
	}
	return it_works;
}