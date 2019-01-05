#include "pch.h"
#include <stdio.h>
#include "MapManagerSingleton.h"
#include "Map_Node.h"
#include "Tests.h"

extern "C"
{
	__declspec(dllexport) int RunTests()
	{
		return Tests::Run_All_Tests(true);
	}
}

extern "C"
__declspec(dllexport) void AddNode()
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	singleton->Add_Node(new Map_Node());
}

extern "C"
__declspec(dllexport) int GetNumberOfNodes()
{
	return Map_Node::Get_Number_Of_Nodes(); 
}