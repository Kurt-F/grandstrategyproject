#ifndef  ARMYMANAGER
#define ARMYMANAGER

#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif
#include <list>
#include <map>
#include <tuple>
#include <vector>
#include "Army.h"
#include "OpenCLContext.h"

#define ARMY_MAX_SIZE 25;
#define UNIT_LENGTH 25;
#define MAX_NUM_ARMIES 20000;

class ArmyManagerSingleton {
private:
	OpenCLContext context;
	static ArmyManagerSingleton* instance;
	ArmyManagerSingleton();
	std::list<int> used_indices;
	std::list<int> free_indices;
	std::list <std::tuple <cl_kernel, int, int >> engagements;
	std::map<int, int> index_to_id;
	cl_mem* armies;
	cl_program program;


public:
	static ArmyManagerSingleton* get_instance();
	Army* get_army(int index);
	void initArmy(int index, int size);

};
#endif // ! ARMYMANAGMENT