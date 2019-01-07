#pragma once
#include "Connection.h"
#include "json.hpp"

// Terrain constants
#define FOOTHILLS 0
#define DESERT 1
#define DECIDUOUS 2
// Flag constants
#define IS_OCEAN 0x1;
// Misc constants
#define MAX_NUM_CONNECTIONS 20
#define MAX_NUMBER_OF_NODES 500000
// TODO: add better terrain

class Map_Node
{
private:
	static int number_of_nodes;
	int map_id;
	unsigned char number_of_connections;
	Connection* connections;
	unsigned char flags;
	unsigned char port_level;
	unsigned char airport_level;
	unsigned char elevator_level;
	unsigned char polity; // PLACEHOLDER VARIABLE
	unsigned char climate; 
	float nuclear_contamination;
	float chemical_contamination;
	int area; // Square miles
	int terrain;
	float atmosphere; // Oxygen density?
	float air_quality; // The relative presence of contaminants harmful to human breathing
	int resource_type; // Needs constants, maybe import from an economics header file
	int resource_amount; // Measured in tons
	nlohmann::json Connection_To_JSON(Connection c);

public:
	Map_Node();
	// Should ONLY be used for creating nodes in previously used memory, in singleton
	Map_Node(int id);
	// ~Map_Node(); Since all of our Map_Nodes are not dynamic, we will have a delete function that essentially sets it to the Map_Node equal of "NULL"
	bool DeleteMapNode(int pseudo_ptr);
	int Get_ID();
	int Get_Number_Of_Connections();
	int Get_ID_Of_Connection(int index);
	bool Add_Connection(Connection c);
	bool Has_Connection_Index(int index);
	bool Has_Connection(Map_Node m);
	bool Delete_Connection(int id);
	nlohmann::json To_JSON();
	static Map_Node* From_JSON(nlohmann::json n);
	static int Get_Number_Of_Nodes();
	// Flags
	bool Check_Flag(unsigned char f); // Returns true if the given flag f is set
	void Set_Flag(unsigned char f); // Sets the given flag to true
	void Toggle_Flag(unsigned char f); // Inverts the state of the given flag
	// Setters
	void Set_Port_Level(unsigned char p);
	void Set_Airport_Level(unsigned char a);
	void Set_Elevator_Level(unsigned char e);
	void Set_Climate(unsigned char c);
	void Set_Nuclear_Contamination(float n);
	void Set_Chemical_Contamination(float c);
	void Set_Area(int a);
	void Set_Terrain(int t);
	void Set_Atmosphere(int a);
	void Set_Air_Quality(int q);
	void Set_Resource_Type(int r);
	void Set_Resource_Amount(int a);
	// Getters
	unsigned char Get_Port_Level();
	unsigned char Get_Airport_Level();
	unsigned char Get_Elevator_Level();
	unsigned char Get_Climate();
	float Get_Nuclear_Contamination();
	float Get_Chemical_Contamination();
	int Get_Area();
	int Get_Terrain();
	int Get_Atmosphere();
	int Get_Air_Quality();
	int Get_Resource_Type();
	int Get_Resource_Amount();
};

