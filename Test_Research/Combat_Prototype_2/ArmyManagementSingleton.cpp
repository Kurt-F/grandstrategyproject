#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif
#include <list>
#include "ArmyManagementSingleton.h"

void CheckError(cl_int error)
{
	if (error != CL_SUCCESS) {
		std::cerr << "OpenCL call failed with error " << error << std::endl;
		std::exit(1);
	}
}
ArmyManagerSingleton* ArmyManagerSingleton::instance;

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
			armies[i] = clCreateBuffer(context, CL_MEM_READ_WRITE, max_army_size * unit_length * sizeof(float), nullptr, &error);
			CheckError(error);
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
