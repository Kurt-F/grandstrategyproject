#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#ifdef __APPLE__
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif

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
	return program;
}

int main()
{
	typedef unsigned char byte;
	const int DIVISION_WIDTH = 24; 
	const int START_HP = 100;
	const int ATTK_POW = 30;
	const int DEF_POW = 25;
	cl_uint platformIdCount = 0;
	// Here we get the number of platforms
	clGetPlatformIDs(0, nullptr, &platformIdCount);
	std::vector<cl_platform_id> platformIds(platformIdCount);
	// Here we get the information for each platform
	clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);
	cl_uint deviceIdCount = 0;
	// Get the number of devices for that platform
	clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceIdCount);
	std::vector<cl_device_id> deviceIds(deviceIdCount);
	// Get all of the device information for that platformm
	clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, deviceIdCount, deviceIds.data(), nullptr);
	// Create context properties
	cl_context_properties context_properties[] =
	{
		CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(platformIds[0]),
		0
	};

	cl_int error = CL_SUCCESS;
	// Create the actual context
	cl_context context = clCreateContext(context_properties, deviceIdCount, deviceIds.data(), nullptr, nullptr, &error);
	CheckError(error);
	// Create the program by 
	// A: Loading the file
	// B: Creating a program from the contents of that file
	cl_program program = CreateProgram(LoadKernel("fight.cl"), context);
	CheckError(error);
	CheckError(clBuildProgram(program, deviceIdCount, deviceIds.data(), nullptr, nullptr, nullptr));
	std::vector<byte> vec_attk_hp(DIVISION_WIDTH), vec_def_hp(DIVISION_WIDTH), vec_attk_pow(DIVISION_WIDTH), vec_def_pow(DIVISION_WIDTH);
	// Create a kernel for the program
	cl_kernel kernel = clCreateKernel(program, "FIGHT", &error);
	cl_kernel kernel2 = clCreateKernel(program, "DEFEND", &error);
	CheckError(error);
	for (int i = 0; i < vec_attk_hp.size(); i++)
	{
		vec_attk_hp[i] = START_HP;
		vec_def_hp[i] = START_HP;
		vec_attk_pow[i] = ATTK_POW + (i % 5);
		vec_def_pow[i] = DEF_POW + (i % 6);
	}
	cl_mem attk_hp_buf = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(byte) * vec_attk_hp.size(), vec_attk_hp.data(), &error);
	cl_mem def_hp_buf = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(byte) * vec_def_hp.size(), vec_def_hp.data(), &error);
	cl_mem attk_pow_buf = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(byte) * vec_attk_pow.size(), vec_attk_pow.data(), &error);
	cl_mem def_pow_buf = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(byte) * vec_attk_pow.size(), vec_attk_pow.data(), &error);
	CheckError(error);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &attk_hp_buf);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &def_hp_buf);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &attk_pow_buf);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), &def_pow_buf);
	clSetKernelArg(kernel2, 0, sizeof(cl_mem), &attk_hp_buf);
	clSetKernelArg(kernel2, 1, sizeof(cl_mem), &def_hp_buf);
	clSetKernelArg(kernel2, 2, sizeof(cl_mem), &attk_pow_buf);
	clSetKernelArg(kernel2, 3, sizeof(cl_mem), &def_pow_buf);
	CheckError(error);
	const size_t globalWorkSize[] = { DIVISION_WIDTH, 0, 0 };
	std::cout << "Initial Division\n";
	for (int i = 0; i < DIVISION_WIDTH; i++)
	{
		std::cout << (int)vec_def_hp[i] << std::endl;
	}
	cl_command_queue queue = clCreateCommandQueue(context, deviceIds[0], 0, &error);
	bool dead = false; 
	int wave = 1;
	
	while (!dead)
	{
		std::cout << "Wave " << wave++ << std::endl;
		CheckError(clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr));
		CheckError(clEnqueueNDRangeKernel(queue, kernel2, 1, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr));
		CheckError(clEnqueueReadBuffer(queue, attk_hp_buf, CL_TRUE, 0, sizeof(byte) * DIVISION_WIDTH, vec_attk_hp.data(), 0, nullptr, nullptr));
		CheckError(clEnqueueReadBuffer(queue, def_hp_buf, CL_TRUE, 0, sizeof(byte) * DIVISION_WIDTH, vec_def_hp.data(), 0, nullptr, nullptr));
		CheckError(error);
		bool attk_dead = true; 
		bool def_dead = true; 
		for (int i = 0; i < vec_attk_hp.size(); i++)
		{
			attk_dead = attk_dead && (vec_attk_hp[i] <= 0);
			def_dead = def_dead && (vec_def_hp[i] <= 0);
		}
		dead = attk_dead || def_dead;  
	}

	for (int i = 0; i < DIVISION_WIDTH; i++)
	{
		std::cout << (int)vec_def_hp[i] << std::endl;
	}
	return 0;
}
