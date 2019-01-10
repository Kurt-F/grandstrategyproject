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
	struct Map_Node_Struct
	{
		int32_t map_id;
		int32_t area;
		int32_t terrain;
		int32_t number_of_connections;
		int32_t*connection_ids;
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
__declspec(dllexport) void ReadNodeAtIndex(Map_Node_Struct *m_struct, int index)
{
	MapManagerSingleton *instance = MapManagerSingleton::Get_Instance();
	if (index < 0 || index >= Map_Node::Get_Number_Of_Nodes())
	{
		m_struct->area = -1;
		m_struct->connection_ids = nullptr; 
		m_struct->map_id = -1;
		m_struct->number_of_connections = -1;
		m_struct->terrain = -1;
		return;
	}
	else
	{
		Map_Node *node = instance->Get_Node(index);
		m_struct->area = node->Get_Area();
		m_struct->map_id = node->Get_ID();
		m_struct->number_of_connections = node->Get_Number_Of_Connections();
		m_struct->terrain = node->Get_Terrain(); 
		if (m_struct->number_of_connections > 0)
		{
			m_struct->connection_ids = new int32_t[node->Get_Number_Of_Connections()];
			for (int i = 0; i < m_struct->number_of_connections; i++)
			{
				m_struct->connection_ids[i] = node->Get_ID_Of_Connection(i);
			}
		}
	}
}

extern "C"
__declspec(dllexport) void AddNode()
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	singleton->Add_Node(new Map_Node());
}

extern "C"
__declspec(dllexport) int RemoveNode(int index)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Remove_Node(index);
}

extern "C"
__declspec(dllexport)  int CreateConnection(int index_a, int index_b, double freight_cost_per_lb, double travel_cost)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Create_Connection(index_a, index_b, freight_cost_per_lb, travel_cost);
}

extern "C"
__declspec(dllexport) int RemoveConnection(int index_a, int index_b)
{
	MapManagerSingleton *singleton = MapManagerSingleton::Get_Instance();
	return (int)singleton->Remove_Connection(index_a, index_b);
}

extern "C"
__declspec(dllexport) int EditMapNode(int map_node_num, int what_is_being_changed, int val)
{
	Map_Node *mp = MapManagerSingleton::Get_Instance()->Get_Node(map_node_num);
	if (what_is_being_changed == 0)
	{
		mp->Set_Port_Level(val);
	}
	else if (what_is_being_changed == 1)
	{
		mp->Set_Terrain((unsigned char)val);
	}
	else
	{
		mp->Set_Climate((unsigned char)val);
	}
	return 0;
}

extern "C"
__declspec(dllexport) int GetNumberOfNodes()
{
	return Map_Node::Get_Number_Of_Nodes(); 
}

// End functions for connecting to the map singleton