#pragma once
#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif

#ifndef  ARMYMANAGMENT
#define ARMYMANAGMENT


#include <list>
#include "Army.h"
#include "OpenCLContext.h"

#define ARMY_MAX_SIZE 25;
#define UNIT_LENGTH 25;
#define MAX_NUM_ARMIES 20000;

class ArmyManagerSingleton {
private:
	cl_context context;
	ArmyManagerSingleton();
	std::list<int> used_indices;
	std::list<int> free_indices;
	cl_mem* armies;
	static ArmyManagerSingleton* instance;
public:
	static ArmyManagerSingleton* get_instance();
	Army* get_army(int index);
};
#endif // ! ARMYMANAGMENT