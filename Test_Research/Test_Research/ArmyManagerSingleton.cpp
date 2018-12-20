#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif

#ifndef  ARMYMANAGMENT
#define ARMYMANAGMENT


#include <list>
#include "Army.cpp"
#include "OpenCLContext.cpp"

#define ARMY_MAX_SIZE 25;
#define UNIT_LENGTH 25;
#define MAX_NUM_ARMIES 20000;

class ArmyManagerSingleton {
private:
	cl_context context;
	ArmyManagerSingleton() {
		int limit = MAX_NUM_ARMIES;
		for (int i = 0; i < limit; i++) {
			free_indices.push_back(i);
		}
		context = OpenCLContext::CreateCLContext();
		int max_num_armies = MAX_NUM_ARMIES;
		int max_army_size = ARMY_MAX_SIZE;
		int unit_length = UNIT_LENGTH; 
		armies = new cl_mem[max_num_armies];
		cl_int error = 0; 
		for (int i = 0; i < max_num_armies; i++)
		{
			armies[i] = clCreateImage2D(context, CL_MEM_READ_WRITE, NULL, max_army_size * sizeof(float), unit_length * sizeof(float), 0, NULL, &error);
		}
	}
	std::list<int> used_indices;
	std::list<int> free_indices;
	cl_mem* armies;
	static ArmyManagerSingleton* instance;
public:
	static ArmyManagerSingleton* get_instance() {
		if (instance == nullptr) {
			instance = new ArmyManagerSingleton();
		}
		return instance;
	}
	Army* get_army(int index) {
		return nullptr;
	}
};
#endif // ! ARMYMANAGMENT