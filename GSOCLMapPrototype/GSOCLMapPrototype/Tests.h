#pragma once
#include <iostream>
// Static class :p
// This is a sort of "Unit Test" file for all of the tests as the project grows on the C++ end. 


	class Tests
	{
		public:
		static void Print_Test_Results(bool pass_fail, std::string name_of_message, std::string message);
		static bool Run_All_Tests(bool recursive_print_results);
		static bool Run_Map_Tests(bool print_results, bool recursive_print_results);
		static bool Run_FIO_Tests(bool print_results, bool recursive_print_results);
		static bool Create_MapManagerSingleton(bool print_results); // Run this test first
		static bool Add_Nodes(bool print_results);
		static bool Create_Connections(bool print_results);
		static bool Remove_Connections(bool print_results);
		static bool Remove_Nodes(bool print_results);
		static bool Save_File_Test(bool print_results);
	};
