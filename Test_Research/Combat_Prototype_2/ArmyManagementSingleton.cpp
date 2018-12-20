#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif
#include <list>
#include "ArmyManagementSingleton.h"

#define ARMY_MAX_SIZE 25;
#define UNIT_LENGTH 25;
#define MAX_NUM_ARMIES 20000;


 ArmyManagerSingleton::ArmyManagerSingleton() {
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

	ArmyManagerSingleton* ArmyManagerSingleton::get_instance() {
		if (instance == nullptr) {
			instance = new ArmyManagerSingleton();
		}
		return instance;
	}
	Army* ArmyManagerSingleton::get_army(int index) {
		return nullptr;
	}
