#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif
#include <list>
#include <fstream>
#include "ArmyManagementSingleton.h"

void CheckError(cl_int error)
{
	if (error != CL_SUCCESS) {
		std::cerr << "OpenCL call failed with error " << error << std::endl;
		std::exit(1);
	}
}

std::string LoadKernel(const char* name)
{
	std::ifstream in(name);
	std::string result(
		(std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	return result;
}

cl_program CreateProgram(const std::string& source,
	cl_context context)
{
	size_t lengths[1] = { source.size() };
	const char* sources[1] = { source.data() };

	cl_int error = 0;
	cl_program program = clCreateProgramWithSource(context, 1, sources, lengths, &error);
	CheckError(error);

	return program;
}

ArmyManagerSingleton* ArmyManagerSingleton::instance;

 ArmyManagerSingleton::ArmyManagerSingleton() {
		
	 int limit = MAX_NUM_ARMIES;
		for (int i = 0; i < limit; i++) {
			free_indices.push_back(i);
		}
		context = OpenCLContext();
		int max_num_armies = MAX_NUM_ARMIES;
		int max_army_size = ARMY_MAX_SIZE;
		int unit_length = UNIT_LENGTH;
		armies = new cl_mem[max_num_armies];
		cl_int error = 0;
		for (int i = 0; i < max_num_armies; i++)
		{
			armies[i] = clCreateBuffer(context.GetClContext(), CL_MEM_READ_WRITE, max_army_size * unit_length * sizeof(float), nullptr, &error);
			CheckError(error);
		}
		program = CreateProgram(LoadKernel("saxpy.cl"),
			context.GetClContext());

		CheckError(clBuildProgram(program, context.getDeviceIdCount(), context.getDeviceIds().data(), nullptr, nullptr, nullptr));
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

	void ArmyManagerSingleton::initArmy(int index, int size)
	{

	}
