#ifndef  ARMYMANAGER
#define ARMYMANAGER

#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif



#include <list>
#include <map>
#include "Army.h"
#include "OpenCLContext.h"

#define ARMY_MAX_SIZE 25;
#define UNIT_LENGTH 25;
#define MAX_NUM_ARMIES 20000;

class ArmyManagerSingleton {
private:
	cl_context context;
	static ArmyManagerSingleton* instance;
	ArmyManagerSingleton();
	std::list<int> used_indices;
	std::list<int> free_indices;
	std::map<int, int> index_to_id;
	cl_mem* armies;

public:
	static ArmyManagerSingleton* get_instance();
	Army* get_army(int index);
};
#endif // ! ARMYMANAGMENT