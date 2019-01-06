#include "pch.h"
#include <stdio.h>
#include "MapManagerSingleton.h"
#include "Map_Node.h"
#include "Tests.h"

extern "C"
{
	struct Test_Struct
	{
		int32_t x;
		double y;
		char z; 
		int32_t* list;
		int32_t size_of_list;
	};
}

extern "C"
{
	__declspec(dllexport) void DoNothing()
	{
		int x = 2; 
	}
}

extern "C"
{
	__declspec(dllexport) int Add(int x, int y)
	{
		return x + y; 
	}
}

extern "C"
{
	__declspec(dllexport) void Add_Many(int* nums, int size)
	{
		nums = new int[size];
		for (int i = 0; i < size; i++)
		{
			nums[i] = i * 2;
		}
	}
}

extern "C"
{
	__declspec(dllexport) void TestStructures(int* test)
	{
		Test_Struct *s = (Test_Struct*)(test);
		s->x = 2;
		s->y = 27.2; 
		s->z = 'z';
		s->size_of_list = 2; 
		s->list = new int[s->size_of_list];
		for (int32_t i = 0; i < s->size_of_list; i++)
		{
			s->list[i] = i;
		}
	}
}

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