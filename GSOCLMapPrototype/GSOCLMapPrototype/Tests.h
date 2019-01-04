#pragma once
#include <iostream>
// Static class :p
// This is a sort of "Unit Test" file for all of the tests as the project grows on the C++ end. 

namespace Tests
{
	void Print_Test_Results(bool pass_fail, std::string name_of_message, std::string message);
	bool Run_All_Tests(bool recursive_print_results);
	bool Run_Map_Tests(bool print_results, bool recursive_print_results);
	bool Create_MapManagerSingleton(bool print_results); // Run this test first
	bool Add_Nodes(bool print_results);
	bool Create_Connections(bool print_results);
	bool Remove_Connections(bool print_results);
	bool Remove_Nodes(bool print_results);
}