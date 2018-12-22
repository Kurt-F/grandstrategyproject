#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif
#include <list>
#include <fstream>
#include "ArmyManagementSingleton.h"
#include <chrono>
#include <ctime>

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
		program = CreateProgram(LoadKernel("Army.cl"),
			context.GetClContext());

		CheckError(clBuildProgram(program, context.getDeviceIdCount(), context.getDeviceIds().data(), nullptr, nullptr, nullptr));
		queue = clCreateCommandQueue(context.GetClContext(), context.getDeviceIds().data()[0],
			CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &error);
		CheckError(error);
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

	void ArmyManagerSingleton::initArmy(int size)
	{
		int max_num_armies = MAX_NUM_ARMIES;
		cl_kernel* kernels = new cl_kernel[max_num_armies];
		cl_int error = 0;
		const size_t globalWorkSize[] = { 25, 0, 0 };
		static const int UNIT_SIZE = 25; 
		std::cout << "Start\n";
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < max_num_armies; i++)
		{
			kernels[i] = clCreateKernel(program, "INIT", &error);
			CheckError(error);
			clSetKernelArg(kernels[i], 0, sizeof(cl_mem), &armies[i]);
			clSetKernelArg(kernels[i], 1, sizeof(int), &UNIT_SIZE);
			
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std:: chrono::seconds>(end - start).count() << std::endl;
			std::cout << "End\n";
			for (int i = 0; i < max_num_armies; i++)
			{
				CheckError(clEnqueueNDRangeKernel(queue, kernels[i], 1, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr));
			}

			for (int i = 0; i < max_num_armies; i++)
			{
				CheckError(clEnqueueNDRangeKernel(queue, kernels[i], 1, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr));
			}
		
		
		CheckError(error);
		float* stuff = new float[25 * 25 * sizeof(float)];
		clEnqueueReadBuffer(queue, armies[185], CL_TRUE, 0, 25 * 25 * sizeof(float), stuff, 0, nullptr, nullptr);
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				std::cout << stuff[i * 25 + j] << " ";
			}
			std::cout << "\n";
		}
	}
