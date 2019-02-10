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
	struct Map_Node_DLL
	{
		char* name;
		int map_id;
		/* std::vector<Connection> connections; Vectors do not work well with C# marshalling. We would have to make an equivalent C# vector type
		or create a dummy variable to hold it. Regardless, this should be fine since external functions should be used to modify the Connections vector
		Also, we don't want to send back pointers to the map_nodes in C++ as to avoid accidental modifications. Thus, copying them into this struct
		should not be terribly wasteful */
		unsigned char surface;
		int terrain;
		unsigned char port_level;
		unsigned char airport_level;
		unsigned char elevator_level;
		unsigned char polity; // PLACEHOLDER
		unsigned char climate; // PLACEHOLDER
		float nuclear;
		float chemical;
		int area; // Square miles
		float oxygen; // Oxygen ppm per cubic foot or something
		float air_quality; // Measure of common pollutants
		int resource_type; // PLACEHOLDER
		int resource_amount; // Tons of the resource available
	};
}

// Begin test functions that do not do anything important
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
		s->list = new int32_t[s->size_of_list];
		for (int32_t i = 0; i < s->size_of_list; i++)
		{
			s->list[i] = i;
		}
	}
}
// End functions that do not do much of anything

// Functions for connecting to the map singleton
extern "C"
{
	__declspec(dllexport) int RunTests()
	{
		return Tests::Run_All_Tests(true);
	}
}


extern "C"
__declspec(dllexport) void ReadNodeAtIndex(Map_Node_DLL *m_struct, int index)
{
	MapManagerSingleton *instance = MapManagerSingleton::Get_Instance();
	if (index < 0 || index >= instance->Get_Number_Of_Nodes())
	{
		m_struct->name = (char*)std::string("yes").c_str();
		m_struct->map_id = -1;
		m_struct->surface = 0;
		m_struct->terrain = 0;
		m_struct->port_level = 0;
		m_struct->elevator_level = 0;
		m_struct->polity = 0;
		m_struct->climate = 0;
		m_struct->nuclear = -1;
		m_struct->chemical = -1; 
		m_struct->area = -1;
		m_struct->oxygen = -1;
		m_struct->air_quality = -1;
		m_struct->resource_type = -1;
		m_struct->resource_amount = -1;
	}
	else
	{
		Map_Node *node = instance->Get_Node(index);
		m_struct->name = (char*)node->name.c_str();
		m_struct->map_id = node->map_id; 
		m_struct->surface = node->surface;
		m_struct->terrain = node->terrain;
		m_struct->port_level = node->port_level;
		m_struct->elevator_level = node->elevator_level;
		m_struct->polity = node->polity;
		m_struct->climate = node->climate; 
		m_struct->nuclear = node->nuclear;
		m_struct->chemical = node->chemical;
		m_struct->area = node->area;
		m_struct->oxygen = node->oxygen;
		m_struct->air_quality = node->air_quality;
		m_struct->resource_type = node->resource_type;
		m_struct->resource_amount = node->resource_amount;
	}
}

extern "C"
__declspec(dllexport) void WriteNodeAtIndex(Map_Node_DLL *m_struct, int index)
{
	MapManagerSingleton *instance = MapManagerSingleton::Get_Instance();
	if (index < 0 || index >= instance->Get_Number_Of_Nodes())
	{
		return;
	}
	else
	{
		Map_Node *node = instance->Get_Node(index);
		node->name = m_struct->name;
		node->map_id = m_struct->map_id;
		node->surface = m_struct->surface;
		node->terrain = m_struct->terrain;
		node->port_level = m_struct->port_level;
		node->elevator_level = m_struct->elevator_level;
		node->polity = m_struct->polity;
		node->climate = m_struct->climate;
		node->nuclear = m_struct->nuclear;
		node->chemical = m_struct->chemical;
		node->area = m_struct->area;
		node->oxygen = m_struct->oxygen;
		node->air_quality = m_struct->air_quality;
		node->resource_type = m_struct->resource_type;
		node->resource_amount = m_struct->resource_amount;
	}
}

extern "C"
__declspec(dllexport) int AddNode()
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	Map_Node *node = singleton->Create_Map_Node();
	singleton->Add_Node(node);
	return node->map_id;
}

extern "C"
__declspec(dllexport) int RemoveNode(int index)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Remove_Node(index);
}

extern "C"
__declspec(dllexport) int CreateConnectionBothWays(int index_a, int index_b, double freight_cost_per_lb, double travel_cost)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Create_Connection(index_a, index_b, freight_cost_per_lb, travel_cost) + 
		(int)singleton->Create_Connection(index_b, index_a, freight_cost_per_lb, travel_cost);
}

extern "C"
__declspec(dllexport) int CreateConnection(int index_a, int index_b, double freight_cost_per_lb, double travel_cost)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Create_Connection(index_a, index_b, freight_cost_per_lb, travel_cost);
}

extern "C"
__declspec(dllexport) int RemoveConnectionBothWays(int index_a, int index_b)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Remove_Connection(index_a, index_b) + (int)singleton->Remove_Connection(index_b, index_a);
}

extern "C"
__declspec(dllexport) int RemoveConnection(int index_a, int index_b)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Remove_Connection(index_a, index_b);
}

extern "C"
__declspec(dllexport) int GetNumberOfNodes()
{
	return MapManagerSingleton::Get_Instance()->Get_Number_Of_Nodes(); 
}

// End functions for connecting to the map singleton