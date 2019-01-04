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
	return true;
}

bool Tests::Create_MapManagerSingleton(bool print_results)
{
		MapManagerSingleton *i = MapManagerSingleton::Get_Instance();
		MapManagerSingleton *j = MapManagerSingleton::Get_Instance();

		
		return true;
}

